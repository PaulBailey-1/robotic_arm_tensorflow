#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "Camera.hpp"

Camera::Camera() {
    _cap = cv::VideoCapture(0);
    _cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
    if (!_cap.isOpened()) {
        printf("ERROR: Unable to open the camera\n");
    } else
        printf("Camera Feed Opened\n");
}

void Camera::getFrame(unsigned char* &data, unsigned int &size) {
    static cv::Mat frame;
    _cap >> frame;
    data = frame.data;
    size = frame.total() * frame.elemSize();
}