
#include "RobotControl.hpp"

RobotControl::RobotControl(Client* client) {
    _client = client;
}

void RobotControl::controlLoop() {
    while (!_termination) {
        if (_targetPresent) {
            printf("Target detection aquired-\n%s\n", _target.toString().c_str());
            _alignmentError = _target.scaleWidth / 2 - _target.centerX;
            double movement = std::round(_alignmentError) * 0.001;
            if (std::abs(movement) > 0.1) {
                std::string direction;
                if (std::round(movement) == std::abs(std::round(movement))) {
                    direction = "-1";
                } else {
                    direction = "1";
                }
                printf("Target x: %i Error: %f Moving for %fs in direction %s\n", _target.centerX, _alignmentError, movement, direction.c_str());
                _client->sendCommand("base move " + direction + " " + std::to_string(movement));
            }
        }
        sleep(5);
    }
}