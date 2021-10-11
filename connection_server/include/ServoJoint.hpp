#ifndef SERVO_JOINT
#define SERVO_JOINT

#include <chrono>

#include "Servo.hpp"

class ServoJoint : public Servo {
    public:
        ServoJoint(int port);
        ServoJoint();

        void rotate(float speed); // 1 to -1
        void updateMotion();
        void move(int dir, double time); // CW = 1, CC = -1
    
    private:
        double _motionTime = 0;
        std::chrono::steady_clock::time_point _motionBegin;
};

#endif