#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/core/ocl.hpp>

#include "Output.hpp"
#include "RobotArm.hpp"
#include "Detection.hpp"

#define KEYCOMMAND_MS 200

Output::Output(RobotArm* robotArm) {
    _robotArm = robotArm;
    _frameCount = 0;
    for(int i=0;i<16;i++) _FPS[i]=0.0;

}

void Output::frameUpdate(cv::Mat frame) {

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

    char key = cv::pollKey();

    switch(key) {
        case 27:
            terminated = true;
            std::cout << "Ouput terminated\n";
            break;
        case 82: // Up
            _robotArm->elbow.move(CW, KEYCOMMAND_MS);
            break;
        case 84: // Down
            _robotArm->elbow.move(CC, KEYCOMMAND_MS);
            break;
        case 81: // Left
            _robotArm->base.move(CC, KEYCOMMAND_MS);
            break;
        case 83: // Right
            _robotArm->base.move(CW, KEYCOMMAND_MS);
            break;
        case 225: // Out
            _robotArm->arm.move(CC, KEYCOMMAND_MS);
            break;
        case 228: // In
            _robotArm->arm.move(CW, KEYCOMMAND_MS);
            break;
        case 122: // Open
            _robotArm->claw.open();
            break;
        case 120: // Close
            _robotArm->claw.close();
            break;
        default:
            break;
    }
}

void Output::closeWindow() {
    cv::destroyAllWindows();
}