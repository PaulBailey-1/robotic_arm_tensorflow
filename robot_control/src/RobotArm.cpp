#include "pca9685.h"
#include <wiringPi.h>
#include <iostream>

#include "RobotArm.hpp"

RobotArm::RobotArm() {

    wiringPiSetup();
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		std::cout << "Error in pca9685 setup\n";
	}

    pca9685PWMReset(fd);

	base = ServoJoint(0);
	arm = ServoJoint(1);
	elbow = ServoJoint(2);
	claw = ServoClaw(3);

}

void RobotArm::servoControlLoop() {
	while (!termination) {
		base.updateMotion();
		arm.updateMotion();
		elbow.updateMotion();
	}
	std::cout << "Robot Arm terminated\n";
}