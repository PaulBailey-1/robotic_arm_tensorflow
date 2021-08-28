#include "stdio.h"
#include <thread>
#include <signal.h>

#include "Server.hpp"
#include "Camera.hpp"
#include "RobotArm.hpp"

bool disconnect = false;

void pipeSignalHandler(int signum) {
    disconnect = true;
}

int main() {
    Camera* camera = new Camera();
    RobotArm* robotArm = new RobotArm();
    Server* server = new Server(robotArm);

    signal(SIGPIPE, pipeSignalHandler);

    server->start();

    std::thread serverRecieve(&Server::recieveCommands, server);
    std::thread servoControl(&RobotArm::servoControlLoop, robotArm);


    unsigned char* frameData = 0;
    unsigned int dataSize;

    while (!server->disconnected() && !disconnect) {
        camera->getFrame(frameData, dataSize);
        server->sendData(frameData, dataSize);
    }

    printf("Client disconnected\n");

    server->kill();
    serverRecieve.join();
    robotArm->kill();
    servoControl.join();

    return 0;
}
