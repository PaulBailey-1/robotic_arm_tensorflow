#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/core/ocl.hpp>

#include "Output.hpp"

Output::Output() {
    _frameCount = 0;
    for(int i=0;i<16;i++) _FPS[i]=0.0;
}

void Output::showFrame(cv::Mat frame) {

    _Tend = std::chrono::steady_clock::now();
    //calculate frame rate
    _frameRate = std::chrono::duration_cast <std::chrono::milliseconds> (_Tend - _Tbegin).count();

    _Tbegin = std::chrono::steady_clock::now();

    _FPS[((_frameCount++)&0x0F)]=1000.0/_frameRate;
    _frameRate=0.0;
    for(int i=0; i<16; i++){ _frameRate+=_FPS[i]; }
    _frameRate /= 16;
    cv::putText(frame, cv::format("FPS %0.2f",_frameRate), cv::Point(10,20),cv::FONT_HERSHEY_SIMPLEX,0.6, cv::Scalar(0, 0, 255));

    //show output
    cv::imshow("Robot", frame);

    char esc = cv::waitKey(5);
    if(esc == 27) {
        terminated = true;
        std::cout << "Ouput terminated\n";
    }
}

void Output::closeWindow() {
    cv::destroyAllWindows();
}