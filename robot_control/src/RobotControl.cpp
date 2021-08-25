
#include "RobotControl.hpp"

RobotControl::RobotControl(Client* client) {
    
    base = Joint(client);
    arm = Joint(client);
    elbow = Joint(client);
    claw = Claw(client) ;
}

void RobotControl::controlLoop() {
    while (!_termination) {

    }
    
}