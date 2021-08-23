
#include "RobotControl.hpp"

RobotControl::RobotControl(Client* client) {
    _client = client;
    
    base = Joint(0);
    arm = Joint(1);
    elbow = Joint(2);
    claw = Claw(3) ;
}

void RobotControl::controlLoop() {
    while (!_termination) {

    }
    
}