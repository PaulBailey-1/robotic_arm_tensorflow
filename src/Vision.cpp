#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
#include <opencv2/core/ocl.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/model.h"
#include <cmath>

#include "Vision.hpp"

using namespace std;

Vision::Vision() {

    // // Load model
    // std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("detect.tflite");

    // // Build the interpreter
    // tflite::ops::builtin::BuiltinOpResolver resolver;
    // tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    // interpreter->AllocateTensors();

	// // Get the names
	// bool result = getFileContent("COCO_labels.txt");
	// if(!result)
	// {
    //     cout << "loading labels failed";
    //     exit(-1);
	// }

    _cap = cv::VideoCapture(0);
    if (!_cap.isOpened()) {
        cout << "ERROR: Unable to open the camera" << endl;
    } else
        cout << "Camera Feed Opened" << endl;
}

void Vision::detectionLoop() {

    while(!termination) {

    _cap >> _frame;
    if (_frame.empty()) {
        cerr << "No Camera Feed" << endl;
        return;
    }

    // detection(_frame);

    _processedFrame = _frame;
    newFrame = true;

    }

    _cap.release();
    cout << "Vision terminate\n";
}

// void Vision::detection(cv::mat &src) {
//     Mat image;
//     int cam_width =src.cols;
//     int cam_height=src.rows;

//     // copy image to input as input tensor
//     cv::resize(src, image, Size(width,height));
//     memcpy(interpreter->typed_input_tensor<uchar>(0), image.data, image.total() * image.elemSize());

//     interpreter->SetAllowFp16PrecisionForFp32(true);
//     interpreter->SetNumThreads(4);      //quad core

// //        cout << "tensors size: " << interpreter->tensors_size() << "\n";
// //        cout << "nodes size: " << interpreter->nodes_size() << "\n";
// //        cout << "inputs: " << interpreter->inputs().size() << "\n";
// //        cout << "input(0) name: " << interpreter->GetInputName(0) << "\n";
// //        cout << "outputs: " << interpreter->outputs().size() << "\n";

//     interpreter->Invoke();      // run your model

//     const float* detection_locations = interpreter->tensor(interpreter->outputs()[0])->data.f;
//     const float* detection_classes=interpreter->tensor(interpreter->outputs()[1])->data.f;
//     const float* detection_scores = interpreter->tensor(interpreter->outputs()[2])->data.f;
//     const int    num_detections = *interpreter->tensor(interpreter->outputs()[3])->data.f;

//     //there are ALWAYS 10 detections no matter how many objects are detectable
//     //cout << "number of detections: " << num_detections << "\n";

//     const float confidence_threshold = 0.5;
//     for(int i = 0; i < num_detections; i++){
//         if(detection_scores[i] > confidence_threshold){
//             int  det_index = (int)detection_classes[i]+1;
//             float y1=detection_locations[4*i  ]*cam_height;
//             float x1=detection_locations[4*i+1]*cam_width;
//             float y2=detection_locations[4*i+2]*cam_height;
//             float x2=detection_locations[4*i+3]*cam_width;

//             Rect rec((int)x1, (int)y1, (int)(x2 - x1), (int)(y2 - y1));
//             rectangle(src,rec, Scalar(0, 0, 255), 1, 8, 0);
//             putText(src, format("%s", Labels[det_index].c_str()), Point(x1, y1-5) ,FONT_HERSHEY_SIMPLEX,0.5, Scalar(0, 0, 255), 1, 8, 0);
//         }
//     }
// }

cv::Mat Vision::getFrame() {
    if (newFrame) {
        return _processedFrame;
        newFrame = false;
    } else {
        cout << "Error: Tried to get frame before available\n";
        return cv::Mat();
    }
};