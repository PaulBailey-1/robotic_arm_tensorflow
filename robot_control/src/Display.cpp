#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/ocl.hpp>
#include <string>
#include <stdio.h>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <fstream>

#include "Display.hpp"
#include "RobotControl.hpp"
#include "Detection.hpp"

Display::Display(Client* client) {
    _client = client;
    _frameCount = 0;
    for(int i=0;i<16;i++) _FPS[i]=0.0;

}

void Display::frameUpdate(cv::Mat frame) {

    _Tend = std::chrono::steady_clock::now();
    _frameRate = std::chrono::duration_cast <std::chrono::milliseconds> (_Tend - _Tbegin).count();
    _Tbegin = std::chrono::steady_clock::now();
    _FPS[((_frameCount++)&0x0F)]=1000.0/_frameRate;
    _frameRate=0.0;
    for(int i=0; i<16; i++){ _frameRate+=_FPS[i]; }
    _frameRate /= 16;
    // cv::putText(frame, cv::format("FPS %0.2f",_frameRate), cv::Point(10,20),cv::FONT_HERSHEY_SIMPLEX,0.6, cv::Scalar(0, 0, 255));

    for(int i=0; i<_detections.size(); i++) {
        cv::Rect rec(_detections[i]->box[0], _detections[i]->box[1], _detections[i]->box[2], _detections[i]->box[3]);
        cv::rectangle(frame, rec, cv::Scalar(0, 0, 255), 1, 8, 0);
        cv::putText(frame, cv::format("%s", _detections[i]->name.c_str()), cv::Point(_detections[i]->box[0], _detections[i]->box[1]-5), cv::FONT_HERSHEY_SIMPLEX,0.5, cv::Scalar(0, 0, 255), 1, 8, 0);
    }

    cv::imshow("Robot", frame);

    int key = cv::pollKey();
    // if (key != 255) {
    //     printf("Key - %i", (int)key);
    // }

    switch(key) {
        case 27:
            terminated = true;
            printf("Display terminated\n");
            break;
        case 82: // Up
            _client->sendCommand("elbow move CW " + std::to_string(KEYCOMMAND_MS));
            break;
        case 84: // Down
            _client->sendCommand("elbow move CC " + std::to_string(KEYCOMMAND_MS));
            break;
        case 81: // Left
            _client->sendCommand("base move CC " + std::to_string(KEYCOMMAND_MS));
            break;
        case 83: // Right
            _client->sendCommand("base move CW " + std::to_string(KEYCOMMAND_MS));
            break;
        case 225: // Out
            _client->sendCommand("arm move CC " + std::to_string(KEYCOMMAND_MS));
            break;
        case 228: // In
            _client->sendCommand("arm move CW " + std::to_string(KEYCOMMAND_MS));
            break;
        case 122: // Open
            _client->sendCommand("claw open");
            break;
        case 120: // Close
            _client->sendCommand("claw close");
            break;
        case 112: // Pic
            saveImage(frame);
            break;
        default:
            break;
    }
}

void Display::closeWindow() {
    cv::destroyAllWindows();
}

void Display::saveImage(cv::Mat frame) {
    DIR* dir = opendir("img");
    if (dir) {
        closedir(dir);
    } else if (ENOENT == errno) {
        mkdir("img", 0777);
    }

    if (_img_count == 0) {
        std::ifstream indexFileIn;
        indexFileIn.open("img/index");
        if (indexFileIn) {
            indexFileIn >> _img_count;
        }
        indexFileIn.close();
    }

    _img_count++;
    std::ofstream indexFileOut;
    indexFileOut.open("img/index");
    indexFileOut << _img_count;
    indexFileOut.close();

    cv::imwrite("img/" + std::to_string(_img_count) + ".jpg", frame);
    std::cout << "Saved image " << _img_count << std::endl;
}