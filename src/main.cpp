#include <thread>

#include "RobotArm.hpp"
#include "Vision.hpp"
#include "Output.hpp"

int main() {

    RobotArm robotArm;
    Vision vision;
    Output output;

    std::thread visionThread(&Vision::detectionLoop, &vision);

    while(!output.terminated) {
        if (vision.newFrame) {
            output.showFrame(vision.getFrame());
        }
    }

    output.closeWindow();
    vision.termination = true;
    visionThread.join();

    return 0;
}