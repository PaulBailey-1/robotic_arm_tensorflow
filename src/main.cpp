#include <thread>
#include <vector>

#include "RobotArm.hpp"
#include "Vision.hpp"
#include "Output.hpp"
#include "Detection.hpp"

int main() {

    RobotArm* robotArm = new RobotArm();
    Vision* vision = new Vision();
    Output* output = new Output(robotArm);

    std::thread visionThread(&Vision::detectionLoop, vision);
    std::thread robotArmThread(&RobotArm::servoControlLoop, robotArm);

    while(!output->terminated) {
        std::vector<Detection*> detections = vision->getDetections();
        if (!detections[0]->empty) {
            output->setDetections(detections);
        }
        output->frameUpdate(vision->getFrame());
    }

    output->closeWindow();
    vision->termination = true;
    visionThread.join();
    robotArm->termination = true;
    robotArmThread.join();

    return 0;
}