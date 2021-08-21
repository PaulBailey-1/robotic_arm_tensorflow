#ifndef SERVO_CLAW
#define SERVO_CLAW

#include "Servo.hpp"

#define OPEN_ANGLE 180
#define CLOSE_ANGLE 0

class ServoClaw : Servo {
    public:
        ServoClaw(int port);
        ServoClaw();

        void open();
        void close();
};

#endif