#include <netinet/in.h>

#define PORT 7070
#define BUFFER_SIZE 1024

class Server {
    public:
        Server();
        void start();
        void sendData(unsigned char* data, unsigned int size);
        void recieveCommands();
        void kill();

        bool disconnected() {
            return _disconnect;
        }

    private:
        bool _disconnect = false;

        struct sockaddr_in _address;

        int _server_socket;
        int _client_socket;
        int _opt = 1;
        int _addrlen = sizeof(_address);

        char _buffer[BUFFER_SIZE] = {0};
};