#include "pca9685.h"
#include <wiringPi.h>
#include <stdio.h>

#include "RobotArm.hpp"

RobotArm::RobotArm() {

    wiringPiSetup();
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		printf("Error in pca9685 setup\n");
	}

    pca9685PWMReset(fd);

	base = ServoJoint(0);
	arm = ServoJoint(1);
	elbow = ServoJoint(2);
	claw = ServoClaw(3);

}

void RobotArm::servoControlLoop() {
	while (!_termination) {
		base.updateMotion();
		arm.updateMotion();
		elbow.updateMotion();
	}
	base.rotate(0);
	arm.rotate(0);
	elbow.rotate(0);
	printf("Robot arm terminated\n");
}