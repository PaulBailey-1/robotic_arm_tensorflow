
#include <thread>
#include <vector>

#include "Client.hpp"
#include "RobotArm.hpp"
#include "Vision.hpp"
#include "Output.hpp"
#include "Detection.hpp"

int main() {

    Client* client = new Client();
    RobotArm* robotArm = new RobotArm();
    Vision* vision = new Vision(client);
    Output* output = new Output(robotArm);

    client->connectToRobot();

    std::thread clientThread(&Client::recieveLoop, client);
    std::thread visionThread(&Vision::detectionLoop, vision);
    std::thread robotArmThread(&RobotArm::servoControlLoop, robotArm);

    while(!output->terminated) {
        std::vector<Detection*> detections;
        if (vision->getDetections(detections)) {
            output->setDetections(detections);
        }
        output->frameUpdate(vision->getFrame());
    }

    output->closeWindow();
    client->kill();
    clientThread.join();
    vision->kill();
    visionThread.join();
    robotArm->kill();
    robotArmThread.join();

    return 0;
}