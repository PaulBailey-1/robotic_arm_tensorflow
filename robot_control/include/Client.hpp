
#define PORT 7070
#define FRAME_SIZE 921600

#include <netinet/in.h>

class Client {
    public:
        Client();
        void connectToRobot();
        void recieve();

    private:
        const char* serverIP = "192.168.1.67";
        int _socket = 0;
        struct sockaddr_in _serv_addr;
        char _buffer[FRAME_SIZE] = {0};
};