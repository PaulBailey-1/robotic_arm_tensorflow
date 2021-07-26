#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "Detection.hpp"
#include <opencv2/core/ocl.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/model.h"
#include <cmath>


class Vision {
    public:
        Vision();

        void detectionLoop();
        std::vector<Detection*> getDetections(); 

        cv::Mat getFrame() {
            return _frame;
        }

        bool termination = false;

    private:
        cv::VideoCapture _cap;
        cv::Mat _frame;

        std::unique_ptr<tflite::FlatBufferModel> _model;
        std::vector<std::string> _labels;
        std::unique_ptr<tflite::Interpreter> _interpreter;

        const size_t width = 300;
        const size_t height = 300;

        std::vector<Detection*> _detections;
        bool _newDetections = false;

        bool getFileContent(std::string fileName);

};