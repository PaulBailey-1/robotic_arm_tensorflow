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

#include "Client.hpp"

class Vision {
    public:
        Vision(Client* client);

        void detectionLoop();
        bool getDetections(std::vector<Detection> &out); 

        cv::Mat getFrame() {
            return _frame;
        }

        void kill() {
            _termination = true;
        }


    private:
        Client* _client;

        cv::Mat _frame;

        std::unique_ptr<tflite::FlatBufferModel> _model;
        std::vector<std::string> _labels;
        std::unique_ptr<tflite::Interpreter> _interpreter;

        const size_t tensorsWidth = 192;
        const size_t tensorsHeight = 192;

        int _cam_width;
        int _cam_height;

        std::vector<Detection> _detections;
        bool _newDetections = false;
        bool _termination = false;

        bool getFileContent(std::string fileName);

};