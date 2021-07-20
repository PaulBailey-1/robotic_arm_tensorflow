#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/core/ocl.hpp>
#include <cmath>

class Output {
    public:
        Output();
        void showFrame(cv::Mat frame);
        void closeWindow();

        bool terminated = false;

    private:
        float _frameRate;
        int _frameCount;
        std::chrono::steady_clock::time_point _Tbegin, _Tend;
        float _FPS[16];
        
};