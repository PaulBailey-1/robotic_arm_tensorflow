
#include <thread>
#include <vector>

#include "Client.hpp"
#include "RobotArm.hpp"
#include "Vision.hpp"
#include "Output.hpp"
#include "Detection.hpp"

int main() {

    Client client;
    client.connectToRobot();
    client.recieve();

    // RobotArm* robotArm = new RobotArm();
    // Vision* vision = new Vision();
    // Output* output = new Output(robotArm);

    // std::thread visionThread(&Vision::detectionLoop, vision);
    // std::thread robotArmThread(&RobotArm::servoControlLoop, robotArm);

    // while(!output->terminated) {
    //     std::vector<Detection*> detections;
    //     if (vision->getDetections(detections)) {
    //         output->setDetections(detections);
    //     }
    //     output->frameUpdate(vision->getFrame());
    // }

    // output->closeWindow();
    // vision->termination = true;
    // visionThread.join();
    // robotArm->termination = true;
    // robotArmThread.join();

    return 0;
}