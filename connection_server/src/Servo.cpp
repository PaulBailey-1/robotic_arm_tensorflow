// #include <wiringPi.h>

#include "Servo.hpp"

Servo::Servo(int port) {
    _port = port;
}

Servo::Servo() {
    _port = 0;
}

void Servo::write(int angle) {

    // float millis = angle/180.0f + 1.0f; // Convert 0-180 angle to 1-2 ms
	// float cycleMs = 1000.0f / HERTZ;
	// int tick = (int)(MAX_PWM * millis / cycleMs + 0.5f); // calculate the number of ticks ms
	// pwmWrite(PIN_BASE + _port, tick); // write to servo

}
