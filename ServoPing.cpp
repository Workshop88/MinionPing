/*
 * ServoPing.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: Tom Matukas Workshop88 
 */

#include "ServoPing.h"

ServoPing::ServoPing(uint8_t servo_pin1, uint8_t servo_pin2, uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance){
	commonConstructorRoutines(servo_pin1,ping_trigger_pin, ping_echo_pin,ping_max_cm_distance , servo_pin2);
}

ServoPing::ServoPing(uint8_t servo_pin,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance) {
	commonConstructorRoutines(servo_pin,ping_trigger_pin, ping_echo_pin,ping_max_cm_distance);
}

ServoPing::ServoPing(uint8_t servo_pin,uint8_t ping_pin, unsigned int ping_max_cm_distance){
	commonConstructorRoutines(servo_pin,ping_pin,ping_pin, ping_max_cm_distance);
}

unsigned int ServoPing::UpdateCurrentPosition(){

	if (_pingControlsServos==false)
	{
		return 0;
	}
	if (!_servoPin1Attached)
	{
		_spServo1->attach(_servoPin1);
		_servoPin1Attached=true;
	}
	if (_servoPin2!=NOSERVO2)
	{
		if (!servoPin2Attached)
		{
			_spServo2->attach(_servoPin2);
			servoPin2Attached=true;
		}
	}

	_curPos =_spSonar->ping();
	_spServo1->write((int) map (_curPos,15*US_ROUNDTRIP_CM, 60*US_ROUNDTRIP_CM,0,179));
	_spServo2->write((int) map (_curPos,15*US_ROUNDTRIP_CM, 60*US_ROUNDTRIP_CM,0,179));

	return _curPos;
}

 void ServoPing::commonConstructorRoutines(uint8_t servo_pin1,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance,uint8_t servo_pin2)
{
	_spServo1= new Servo();
	_servoPin1 =servo_pin1;




	if (_servoPin2!=NOSERVO2)
	{
		_spServo2= new Servo();
		_servoPin2 =servo_pin2;
	}

	_spSonar= new NewPing(ping_trigger_pin,ping_echo_pin, ping_max_cm_distance);
	_pingControlsServos=true;
	_curPos=0;
	_servoPin1Attached=false;
	_servoPin2Attached=false;
}

bool ServoPing::getPingState(){
	return _pingControlsServos;
}

void ServoPing::disablePing(){
	_pingControlsServos=false;
}

void ServoPing::enablePing(){
	_pingControlsServos=true;
}


