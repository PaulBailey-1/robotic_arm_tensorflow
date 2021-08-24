#include "stdio.h"
#include <thread>

#include "Server.hpp"
#include "Camera.hpp"
#include "RobotArm.hpp"

int main()
{
    Camera* camera = new Camera();
    RobotArm* robotArm = new RobotArm();
    Server* server = new Server(robotArm);

    std::thread serverRecieve(&Server::recieveCommands, server);
    std::thread servoControl(&RobotArm::servoControlLoop, robotArm);

    server->start();

    unsigned char* frameData = 0;
    unsigned int dataSize;

    while (!server->disconnected()) {
        camera->getFrame(frameData, dataSize);
        server->sendData(frameData, dataSize);
    }

    server->kill();
    serverRecieve.join();
    robotArm->kill();
    servoControl.join();

    return 0;
}
