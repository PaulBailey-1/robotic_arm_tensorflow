#include <netinet/in.h>

#define PORT 7070

class Server {
    public:
        Server();
        void start();
        void sendData(unsigned char* data, unsigned int size);

    private:
        int _server_fd, _client_socket, _valread;
        struct sockaddr_in _address;
        int _opt = 1;
        int _addrlen = sizeof(_address);
        char _buffer[1024] = {0};
};