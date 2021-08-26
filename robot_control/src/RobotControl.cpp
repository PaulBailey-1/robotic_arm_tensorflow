
#include "RobotControl.hpp"

RobotControl::RobotControl(Client* client) {
    _client = client;
}

void RobotControl::controlLoop() {
    while (!_termination) {

    }
    
}