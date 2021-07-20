#include "Servo.hpp"

class ServoJoint : Servo {
    public:
        ServoJoint(int port);
        ServoJoint();

        void rotate(float speed); // 1 to -1
};