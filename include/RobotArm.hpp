#ifndef ROBOT_ARM
#define ROBOT_ARM

#include "ServoJoint.hpp"
#include "ServoClaw.hpp"

class RobotArm {
    public:
        RobotArm();
        void servoControlLoop();
        void rotateBase(int speed);

        bool termination =  false;

        ServoJoint base;
        ServoJoint arm;
        ServoJoint elbow;
        ServoClaw claw;
};

#endif