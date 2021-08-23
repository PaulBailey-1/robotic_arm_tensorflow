#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/ocl.hpp>

#include "RobotArm.hpp"
#include "Detection.hpp"

class Display {
    public:
        Display(RobotArm* robotArm);
        void frameUpdate(cv::Mat frame);
        void closeWindow();

        void setDetections(std::vector<Detection*> detections) {
            _detections = detections;
        }

        bool terminated = false;

    private:
        RobotArm* _robotArm;

        float _frameRate;
        int _frameCount;
        std::chrono::steady_clock::time_point _Tbegin, _Tend;
        float _FPS[16];

        std::vector<Detection*> _detections;

        int _img_count = 0;

        void saveImage(cv::Mat frame);
};