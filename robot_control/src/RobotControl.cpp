
#include "RobotControl.hpp"

RobotControl::RobotControl(Client* client) {
    _client = client;
}

void RobotControl::controlLoop() {
    _client->sendCommand("claw close");
    while (!_termination) {
        
    }
    
}