/*
 * ServoPing.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: jonasthomas
 */

#include "ServoPing.h"

ServoPing::ServoPing(uint8_t servo_pin,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance) {
	commonConstructorRoutines(servo_pin,ping_trigger_pin, ping_echo_pin,ping_max_cm_distance);
}

ServoPing::ServoPing(uint8_t servo_pin,uint8_t ping_pin, unsigned int ping_max_cm_distance){
	commonConstructorRoutines(servo_pin,ping_pin,ping_pin, ping_max_cm_distance);
}

unsigned int ServoPing::UpdateCurrentPosition(){
	if (!servoPinAttached)
	{
		spServo->attach(servoPin);
		servoPinAttached=true;
	}
	curPos =spSonar->ping();
	spServo->write((int) map (curPos,15*US_ROUNDTRIP_CM, 60*US_ROUNDTRIP_CM,0,179));

	return curPos;
}

 void ServoPing::commonConstructorRoutines(uint8_t servo_pin,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance)
{
	spServo= new Servo();
	servoPin =servo_pin;
	spSonar= new NewPing(ping_trigger_pin,ping_echo_pin, ping_max_cm_distance);
	curPos=0;
	servoPinAttached=false;



}


