#ifndef SERVO_JOINT
#define SERVO_JOINT

#include <chrono>

#include "Servo.hpp"

enum Direction { CW = 1, CC = -1};

class ServoJoint : public Servo {
    public:
        ServoJoint(int port);
        ServoJoint();

        void rotate(float speed); // 1 to -1
        void updateMotion();
        void move(Direction dir, int time);
    
    private:
        int _motionTime = 0;
        std::chrono::steady_clock::time_point _motionBegin;
};

#endif