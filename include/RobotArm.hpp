#include "ServoJoint.hpp"
#include "ServoClaw.hpp"

class RobotArm {
    public:
        RobotArm();

    private:
        ServoJoint base;
        ServoJoint arm;
        ServoJoint elbow;

        ServoClaw claw;
};