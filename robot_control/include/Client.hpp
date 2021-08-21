
#define PORT 7070

#include <netinet/in.h>

class Client {
    public:
        Client();
        void connectToRobot();
        void recieve();

    private:
        const char* serverIP = "192.168.1.67";
        static const int frameWidth = 300;
        static const int frameHeight = 225;
        static const int frameSize = frameWidth * frameHeight * 3;
        int _socket = 0;
        struct sockaddr_in _serv_addr;
        char _buffer[frameSize] = {0};
};