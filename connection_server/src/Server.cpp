#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include <vector>

#include "Server.hpp"
#include "RobotArm.hpp"
#include "Servo.hpp"

Server::Server(RobotArm* robotArm) {

    _robotArm = robotArm;
    // Creating socket file descriptor
    if ((_serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &_opt, sizeof(_opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(_serverSocket, (struct sockaddr *)&_address,
             sizeof(_address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(_serverSocket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server created\n");
}

void Server::start() {
    printf("Server started\n");
    if ((_clientSocket = accept(_serverSocket, (struct sockaddr *)&_address, 
    (socklen_t *)&_addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Client connected\n");
}

void Server::sendData(unsigned char* data, unsigned int size) {
    unsigned int bytesSent = 0;
    while (bytesSent < size) {
        bytesSent += send(_clientSocket, data + bytesSent, size - bytesSent, 0);
    }
}

void Server::recieveCommands() {
    while (!_disconnect) {
        int readBytes = 0;
        while (_buffer[readBytes-1] != '/') {
            readBytes += read(_clientSocket, _buffer + readBytes, BUFFER_SIZE - readBytes);
            if (readBytes == -1) {
                if (!_disconnect) {
                    return;
                }
                printf("Server read error - \"%s\"", std::strerror(errno));
            }
        }
        printf("Command - %s\n", _buffer);
        std::string message(_buffer);
        std::string command = message.substr(0, message.length()-1);
        parseCommand(command);
    }
}

void Server::parseCommand(std::string command) {
    std::vector<std::string> parts = split(command, " ");
    Servo* output = 0;

    if (parts[0] == "close") {
        _disconnect = true;
        return;
    }

    if (parts.size() < 2) {
        printf("Command syntax error - \"%s\"", command);
        return;
    }

    if (parts[0] == "base") {
        output = &_robotArm->base;
    } else if (parts[0] == "arm") {
        output = &_robotArm->arm;
    } else if (parts[0] == "elbow") {
        output = &_robotArm->elbow;
    } else if (parts[0] == "claw") {
        output = &_robotArm->claw;
    }

    if (parts[1] == "open") {
        output->open();
        return;
    } else if (parts[1] == "close") {
        output->close();
        return;
    }

    if (parts.size() < 4)
    {
        printf("Command syntax error - \"%s\"", command);
        return;
    }

    if (parts[1] == "move") {
        int time = std::stoi(parts[3]);
        int direction;
        if (parts[2] == "CW") {
            direction = 1;
        }
        else if (parts[2] == "CC") {
            direction = -1;
        }
        output->move((Direction)direction, time);
        return;
    }
    printf("Command not recognized - \"%s\"", command);
}

std::vector<std::string> Server::split(std::string s, std::string del) {
    std::vector<std::string> parts;
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
    _disconnect = true;
    close(_clientSocket);
    close(_serverSocket);
}