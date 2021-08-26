#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/ocl.hpp>

#include "Detection.hpp"
#include "Client.hpp"

#define KEYCOMMAND_MS 200

class Display {
    public:
        Display(Client* client);
        void frameUpdate(cv::Mat frame);
        void closeWindow();

        void setDetections(std::vector<Detection*> detections) {
            _detections = detections;
        }

        bool terminated = false;

    private:
        Client* _client;

        float _frameRate;
        int _frameCount;
        std::chrono::steady_clock::time_point _Tbegin, _Tend;
        float _FPS[16];

        std::vector<Detection*> _detections;

        int _img_count = 0;

        void saveImage(cv::Mat frame);
};