#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <vector

#include "Server.hpp"

Server::Server(RobotArm robotArm) {

    _robotArm = robotArm;
    // Creating socket file descriptor
    if ((_server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &_opt, sizeof(_opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(_server_socket, (struct sockaddr *)&_address,
             sizeof(_address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(_server_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server created\n");
}

void Server::start() {
    printf("Server started\n");
    if ((_client_socket = accept(_server_socket, (struct sockaddr *)&_address, 
    (socklen_t *)&_addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Client connected\n");
}

void Server::sendData(unsigned char* data, unsigned int size) {
    unsigned int bytesSent = 0;
    while (bytesSent < size) {
        bytesSent += send(_client_socket, data + bytesSent, size - bytesSent, 0);
    }
    printf("Sent %u bytes\n", bytesSent);
}

void Server::recieveCommands() {
    while (!_disconnect)
    {
        int readBytes = 0;
        while (_buffer[readBytes-1] == '-')
        {
            readBytes += read(_server_socket, _buffer + readBytes, BUFFER_SIZE - readBytes);
        }
        std::string message(_buffer);
        std::string command = message.substr(0, message.length()-1);
        printf("Command - %s", command);
        parseCommand(command);
    }
}

void Server::parseCommand(String command) {
    std::vector<string> parts = split(command, ' ');
    if (parts[0] == "close") {
        _disconnect = true;
    } else if (parts[0] == "base") {
        if (parts[1] == "move") {
            _robotArm->base.move(parts[2], parts[3]);
        }
    } else if (parts[0] == "arm") {
        if (parts[1] == "move") {
            _robotArm->arm.move(parts[2], parts[3]);
        }
    } else if (parts[0] == "elbow") {
        if (parts[1] == "move") {
            _robotArm->elbow.move(parts[2], parts[3]);
        }
    } else if (parts[0] == "claw") {
        if (parts[1] == "open") {
            _robotArm->claw.open();
        } if (parts[1] == "close") {
            _robotArm->claw.close();
        }
    }
}

std::vector<string> split(string s, string del) {
    std::vector<string> parts;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        parts.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    parts.push_back(s.substr(start, end - start));
    return parts;
}

void Server::kill() {
    close(_client_socket);
    close(_server_socket);
}