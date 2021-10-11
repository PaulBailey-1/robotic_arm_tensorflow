#include <stdio.h>

#include "ServoJoint.hpp"

ServoJoint::ServoJoint(int port) : Servo(port) {}

ServoJoint::ServoJoint() {}

void ServoJoint::rotate(float speed) {
    Servo::write(speed*90 + 90);
}

void ServoJoint::move(float dir, double time) {
    ServoJoint::rotate(dir);
    _motionBegin = std::chrono::steady_clock::now();
    _motionTime = time;
}

void ServoJoint::updateMotion() {
    if (_motionTime > 0.0) {
        std::chrono::steady_clock::time_point Tnow = std::chrono::steady_clock::now();
        float elaspedTime = std::chrono::duration_cast<std::chrono::seconds>(Tnow - _motionBegin).count();
        if (elaspedTime >= _motionTime) {
            rotate(0);
            _motionTime = 0.0;
        }
    }
}