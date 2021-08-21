#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "Server.hpp"

Server::Server() {
    // Creating socket file descriptor
    if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &_opt, sizeof(_opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(_server_fd, (struct sockaddr *)&_address,
             sizeof(_address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(_server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server created\n");
}

void Server::start() {
    printf("Server started\n");
    if ((_client_socket = accept(_server_fd, (struct sockaddr *)&_address,
                                (socklen_t *)&_addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Client connected\n");

    // _valread = read(_client_socket, _buffer, 1024);
    // printf("%s\n", _buffer);
    // send(_client_socket, _hello, strlen(_hello), 0);
    // printf("Hello message sent\n");
}

void Server::sendData(unsigned char* data, unsigned int size) {
    unsigned int bytesSent = 0;
    while (bytesSent < size) {
        bytesSent += send(_client_socket, data + bytesSent, size - bytesSent, 0);
    }
    printf("Sent %u bytes\n", bytesSent);
}