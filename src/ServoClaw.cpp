#include "ServoClaw.hpp"

ServoClaw::ServoClaw(int port) : Servo(port) {}

ServoClaw::ServoClaw() {}

void ServoClaw::open() {
    Servo::write(OPEN_ANGLE);
}

void ServoClaw::close() {
    Servo::write(CLOSE_ANGLE);
}