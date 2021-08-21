#include <stdio.h>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/ocl.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/model.h"
#include <cmath>

#include "Detection.hpp"
#include "Vision.hpp"


using namespace std;

Vision::Vision() {

    _model = tflite::FlatBufferModel::BuildFromFile("model.tflite");

	bool result = getFileContent("labels.txt");
	if(!result)
	{
        cout << "loading labels failed";
        exit(-1);
	}

    _cap = cv::VideoCapture(0);
    _cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
    if (!_cap.isOpened()) {
        cout << "ERROR: Unable to open the camera" << endl;
    } else
        cout << "Camera Feed Opened" << endl;

    _frame = cv::imread("loading.jpg");
}

void Vision::detectionLoop() {

    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder(*_model.get(), resolver)(&_interpreter);

    _interpreter->AllocateTensors();

    while(!termination) {

        _cap >> _frame;
        if (_frame.empty()) {
            cerr << "No Camera Feed" << endl;
            return;
        }

        cv::Mat image;
        int cam_width =_frame.cols;
        int cam_height=_frame.rows;

        cv::resize(_frame, image, cv::Size(width,height));
        memcpy(_interpreter->typed_input_tensor<uchar>(0), image.data, image.total() * image.elemSize());

        _interpreter->SetAllowFp16PrecisionForFp32(true);
        _interpreter->SetNumThreads(4);

        _interpreter->Invoke();

        const float* detection_locations = _interpreter->tensor(_interpreter->outputs()[0])->data.f;
        const float* detection_classes= _interpreter->tensor(_interpreter->outputs()[1])->data.f;
        const float* detection_scores = _interpreter->tensor(_interpreter->outputs()[2])->data.f;
        const int num_detections = *_interpreter->tensor(_interpreter->outputs()[3])->data.f;

        const float confidence_threshold = 0.5;
        _detections.clear();
        for(int i = 0; i < num_detections; i++){
            if(detection_scores[i] > confidence_threshold){
                int  det_index = (int)detection_classes[i]+1;
                float y1=detection_locations[4*i  ]*cam_height;
                float x1=detection_locations[4*i+1]*cam_width;
                float y2=detection_locations[4*i+2]*cam_height;
                float x2=detection_locations[4*i+3]*cam_width;

                int box[4] = {(int)x1, (int)y1, (int)(x2 - x1), (int)(y2 - y1)};
                Detection* detection = new Detection();
                for (int i = 0; i < 4; i++)
                {
                    detection->box[i] = box[i];
                }
                detection->name = _labels[det_index];
                _detections.push_back(detection);
            }
        }
        _newDetections = true;
    }

    _cap.release();
    cout << "Vision terminate\n";
}

bool Vision::getDetections(std::vector<Detection*> &out) {
    if (_newDetections) {
        _newDetections = false;
        out = _detections;
        return true;
    } else {
        return false;
    }
}

bool Vision::getFileContent(std::string fileName) {
	std::ifstream in(fileName.c_str());
	if(!in.is_open()) return false;

	std::string str;
	while (std::getline(in, str))
	{
		if(str.size()>0) _labels.push_back(str);
	}
	in.close();
	return true;
}
