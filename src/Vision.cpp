#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
#include "Detection.hpp"
#include <opencv2/core/ocl.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/model.h"
#include <cmath>

#include "Vision.hpp"


using namespace std;

Vision::Vision() {

    // Load model
    _model = tflite::FlatBufferModel::BuildFromFile("detect.tflite");

	// Get the names
	bool result = getFileContent("COCO_labels.txt");
	if(!result)
	{
        cout << "loading labels failed";
        exit(-1);
	}

    _cap = cv::VideoCapture(0);
    if (!_cap.isOpened()) {
        cout << "ERROR: Unable to open the camera" << endl;
    } else
        cout << "Camera Feed Opened" << endl;

    _frame = cv::imread("loading.jpg");
}

void Vision::detectionLoop() {

    // Build the interpreter
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

        // copy image to input as input tensor
        cv::resize(_frame, image, cv::Size(width,height));
        memcpy(_interpreter->typed_input_tensor<uchar>(0), image.data, image.total() * image.elemSize());

        _interpreter->SetAllowFp16PrecisionForFp32(true);
        _interpreter->SetNumThreads(4); //quad core

        //    cout << "tensors size: " << _interpreter->tensors_size() << "\n";
        //    cout << "nodes size: " << _interpreter->nodes_size() << "\n";
        //    cout << "inputs: " << _interpreter->inputs().size() << "\n";
        //    cout << "input(0) name: " << _interpreter->GetInputName(0) << "\n";
        //    cout << "outputs: " << _interpreter->outputs().size() << "\n";

        _interpreter->Invoke();      // run your model

        const float* detection_locations = _interpreter->tensor(_interpreter->outputs()[0])->data.f;
        const float* detection_classes= _interpreter->tensor(_interpreter->outputs()[1])->data.f;
        const float* detection_scores = _interpreter->tensor(_interpreter->outputs()[2])->data.f;
        const int num_detections = *_interpreter->tensor(_interpreter->outputs()[3])->data.f;

        //there are ALWAYS 10 detections no matter how many objects are detectable
        // cout << "number of detections: " << num_detections << "\n";

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

std::vector<Detection*> Vision::getDetections() {
    if (_newDetections) {
        _newDetections = false;
        return _detections;
    } else {
        std::vector<Detection*> empty;
        empty.push_back(new Detection());
        empty[0]->empty = true;
        return empty;
    }
}

bool Vision::getFileContent(std::string fileName) {
	// Open the File
	std::ifstream in(fileName.c_str());
	// Check if object is valid
	if(!in.is_open()) return false;

	std::string str;
	// Read the next line from File untill it reaches the end.
	while (std::getline(in, str))
	{
		// Line contains string of length > 0 then save it in vector
		if(str.size()>0) _labels.push_back(str);
	}
	// Close The File
	in.close();
	return true;
}
