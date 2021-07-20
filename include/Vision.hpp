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

class Vision {
    public:
        Vision();

        void detectionLoop();
        cv::Mat getFrame();

        bool newFrame = false;
        bool termination =  false;

    private:
        cv::VideoCapture _cap;
        cv::Mat _frame;
        cv::Mat _processedFrame;

        void detection();        
};