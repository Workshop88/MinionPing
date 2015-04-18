/*
 * ServoPing.h
 *
 *  Created on: Apr 18, 2015
 *      Author: Tom Matukas Workshop88
 */

#ifndef SERVOPING_H_
#define SERVOPING_H_
#include <Servo.h>
#include "NewPing.h"
#include "Arduino.h"

class ServoPing {
public:
	ServoPing(uint8_t servo_pin,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance);
	ServoPing(uint8_t servo_pin,uint8_t ping_pin, unsigned int ping_max_cm_distance);

	unsigned int UpdateCurrentPosition();

private:
	Servo * spServo;
	NewPing *spSonar;
    unsigned int curPos;
    unsigned int servoPin;
    bool servoPinAttached;
    void commonConstructorRoutines(uint8_t servo_pin,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance);
};

#endif /* SERVOPING_H_ */
