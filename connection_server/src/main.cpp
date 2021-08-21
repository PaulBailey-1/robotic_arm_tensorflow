#include "stdio.h"

#include "Server.hpp"
#include "Camera.hpp"

int main()
{
    Camera camera;
    Server server;

    server.start();

    unsigned char* frameData = 0;
    unsigned int dataSize;

    camera.getFrame(frameData, dataSize);
    server.sendData(frameData, dataSize);
    return 0;
}
