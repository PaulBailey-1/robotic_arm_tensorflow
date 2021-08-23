#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <opencv2/opencv.hpp>

#include "Client.hpp"

Client::Client() {

    _latestFrame = cv::Mat();

    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error\n");
    }

    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_port = htons(PORT);
}

void Client::connectToRobot() {
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, serverIP, &_serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
    }

    if (connect(_socket, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }
}

void Client::recieveLoop() {
    while (!_termination) {

        int readBytes = 0;
        while (readBytes < frameSize)
        {
            readBytes += read(_socket, _buffer + readBytes, frameSize - readBytes);
        }
        _latestFrame = cv::Mat(frameHeight, frameWidth, CV_8UC3, _buffer);
    }
}

void Client::sendCommand(int port, int angle) {

}