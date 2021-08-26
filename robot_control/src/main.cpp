
#include <thread>
#include <vector>

#include "Client.hpp"
#include "RobotControl.hpp"
#include "Vision.hpp"
#include "Display.hpp"
#include "Detection.hpp"

int main() {

    Client* client = new Client();
    RobotControl* robotControl = new RobotControl(client);
    Vision* vision = new Vision(client);
    Display* display = new Display(client);

    client->connectToRobot();

    std::thread clientThread(&Client::recieveLoop, client);
    std::thread visionThread(&Vision::detectionLoop, vision);
    std::thread robotArmThread(&RobotControl::controlLoop, robotControl);

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
    robotControl->kill();
    robotArmThread.join();

    return 0;
}