#ifndef CLIENT
#define CLIENT

#include <netinet/in.h>
#include <opencv2/opencv.hpp>

#define PORT 7070

class Client {
    public:
        Client();
        void connectToRobot();
        void recieveLoop();
        void sendCommand(int port, int angle);

        cv::Mat getFrame() {
            return _latestFrame;
        }

        void kill() {
            _termination = true;
        }

    private:
        bool _termination = false;

        const char* serverIP = "192.168.1.67";
        static const int frameWidth = 300;
        static const int frameHeight = 225;
        static const int frameSize = frameWidth * frameHeight * 3;
        int _clientSocket = 0;
        struct sockaddr_in _serv_addr;
        char _buffer[frameSize] = {0};

        cv::Mat _latestFrame;
};

#endif