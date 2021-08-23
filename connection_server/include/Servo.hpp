#ifndef SERVO
#define SERVO

#include "Client.hpp"

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

class Servo {
    public:
        Servo(int port);
        Servo();

        void write(int angle);

        static Client* client;
    private:
        int _port;
};

#endif