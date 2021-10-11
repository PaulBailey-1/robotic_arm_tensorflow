
#include "RobotControl.hpp"

RobotControl::RobotControl(Client* client) {
    _client = client;
}

void RobotControl::controlLoop() {
    while (!_termination) {
        if (_targetPresent) {
            printf("Target detection aquired-\n%s", _target->toString());
            _alignmentError = _target->scaleWidth / 2 - _target->centerX;
            double movement = std::round(_alignmentError) * 0.01;
            if (movement > 0.1) {
                printf("Target x: %i Error: %d Moving for %ds\n", _target->x, _alignmentError, movement);
                _client->sendCommand("base move -1 " + std::to_string(movement));
            }
        }
        sleep(5);
    }
}