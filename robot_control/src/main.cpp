
#include <thread>
#include <vector>

#include "Client.hpp"
#include "RobotArm.hpp"
#include "Vision.hpp"
#include "Display.hpp"
#include "Detection.hpp"

int main() {

    Client* client = new Client();
    RobotArm* robotArm = new RobotArm();
    Vision* vision = new Vision(client);
    Display* display = new Display(robotArm);

    client->connectToRobot();

    std::thread clientThread(&Client::recieveLoop, client);
    std::thread visionThread(&Vision::detectionLoop, vision);
    std::thread robotArmThread(&RobotArm::servoControlLoop, robotArm);

    while(!display->terminated) {
        std::vector<Detection*> detections;
        if (vision->getDetections(detections)) {
            display->setDetections(detections);
        }
        display->frameUpdate(vision->getFrame());
    }

    display->closeWindow();
    client->kill();
    clientThread.join();
    vision->kill();
    visionThread.join();
    robotArm->kill();
    robotArmThread.join();

    return 0;
}