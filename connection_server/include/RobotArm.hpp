#ifndef ROBOT_ARM
#define ROBOT_ARM

#include "ServoJoint.hpp"
#include "ServoClaw.hpp"

class RobotArm {
    public:
        RobotArm(Client* client);
        void servoControlLoop();
        void rotateBase(int speed);

        void kill() {
            _termination = true;
        }

        ServoJoint base;
        ServoJoint arm;
        ServoJoint elbow;
        ServoClaw claw;

    private:
        bool _termination =  false;
};

#endif