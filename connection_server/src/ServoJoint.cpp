#include "ServoJoint.hpp"

ServoJoint::ServoJoint(int port) : Servo(port) {}

ServoJoint::ServoJoint() {}

void ServoJoint::rotate(float speed) {
    Servo::write(speed*90 + 90);
}

void ServoJoint::move(int dir, double time) {
    ServoJoint::rotate(dir);
    _motionBegin = std::chrono::steady_clock::now();
    _motionTime = time;
}

void ServoJoint::updateMotion() {
    if (_motionTime > 0.0) {
        std::chrono::steady_clock::time_point Tnow = std::chrono::steady_clock::now();
        double elaspedTime = std::chrono::duration_cast <std::chrono::milliseconds> (Tnow - _motionBegin).count();
        if (elaspedTime <= _motionTime + 0.001) {
            rotate(0);
            _motionTime = 0.0;
        }
    }
}