#include <netinet/in.h>
#include <string>
#include <vector>

#include "RobotArm.hpp"

#define PORT 7070
#define BUFFER_SIZE 1024

class Server {
    public:
        Server(RobotArm* robotArm);
        void start();
        void sendData(unsigned char* data, unsigned int size);
        void recieveCommands();
        void kill();

        bool disconnected() {
            return _disconnect;
        }

    private:
        RobotArm* _robotArm;
        bool _disconnect = false;

        struct sockaddr_in _address;

        int _serverSocket;
        int _clientSocket;
        int _opt = 1;
        int _addrlen = sizeof(_address);

        char _buffer[BUFFER_SIZE] = {0};

        void parseCommand(std::string command);
        std::vector<std::string> split(std::string s, std::string del);
};