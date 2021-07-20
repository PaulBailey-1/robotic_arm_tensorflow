#include "ServoJoint.hpp"

ServoJoint::ServoJoint(int port) : Servo(port) {}

ServoJoint::ServoJoint() {}

void ServoJoint::rotate(float speed) {
    Servo::write(speed*90 + 90);
}