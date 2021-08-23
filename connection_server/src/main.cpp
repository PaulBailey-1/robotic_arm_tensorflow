#include "stdio.h"
#include <thread>

#include "Server.hpp"
#include "Camera.hpp"

int main()
{
    Camera* camera = new Camera();
    Server* server = new Server();

    std::thread serverRecieve(&Server::recieveCommands, server);

    server->start();

    unsigned char* frameData = 0;
    unsigned int dataSize;

    while (!server->disconnected()) {
        camera->getFrame(frameData, dataSize);
        server->sendData(frameData, dataSize);
    }

    server->kill();
    serverRecieve.join();

    return 0;
}
