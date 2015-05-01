/*
 * ServoPing.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: Tom Matukas Workshop88 
 */

#include "ServoPing.h"

ServoPing::ServoPing(uint8_t servoId,uint8_t servo_pin1, uint8_t servo_pin2, uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance,unsigned int rollingAvgCount ){
	commonConstructorRoutines( servoId,servo_pin1,ping_trigger_pin, ping_echo_pin,ping_max_cm_distance, rollingAvgCount , servo_pin2);
}

//ServoPing::ServoPing(uint8_t servo_pin,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance) {
//	commonConstructorRoutines(servo_pin,ping_trigger_pin, ping_echo_pin,ping_max_cm_distance);
//}
//
//ServoPing::ServoPing(uint8_t servo_pin,uint8_t ping_pin, unsigned int ping_max_cm_distance){
//	commonConstructorRoutines(servo_pin,ping_pin,ping_pin, ping_max_cm_distance);
//}

unsigned int ServoPing::UpdateCurrentPosition(){

	if (!_servoPin1Attached)
	{
		_spServo1->attach(_servoPin1);
		_servoPin1Attached=true;
	}

	if (_servoPin2!=NOSERVO2)
	{
		if (!_servoPin2Attached)
		{
			_spServo2->attach(_servoPin2);
			_servoPin2Attached=true;
		}
	}
	Serial.print(F("S"));
	Serial.print(_servoId);

	if (_pingControlsServos==false)
	{
		Serial.print(F("OFF"));
		return _spSonar->ping();
	}


	Serial.print(F("ON"));// Every works as long as this line is in. Makes no sense.

	_curPos =_spSonar->ping();

	_RollingPositionAvg= ((_RollingPositionAvg*RollingAveCount)+_curPos )/(RollingAveCount+1);
	_spServo1->write((int) map (_RollingPositionAvg,3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,0,179));


	_spServo2->write((int) map (_RollingPositionAvg,3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,0,179));

	Serial.print(_RollingPositionAvg);
	Serial.print (F("  "));

	return _curPos;
}

 void ServoPing::commonConstructorRoutines(uint8_t servoId,   uint8_t servo_pin1,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance,unsigned int RollingAvgCount ,uint8_t servo_pin2)
{
	 _servoId=servoId;
	 _spSonar= new NewPing(ping_trigger_pin,ping_echo_pin, ping_max_cm_distance);
	 _pingControlsServos=true;
	 _maxPingDistance =ping_max_cm_distance;
	 _spServo1= new Servo();

	 _servoPin1 =servo_pin1;
	 _RollingPositionAvg=RollingAvgCount;

	if (_servoPin2!=NOSERVO2)
	{
		_spServo2= new Servo();
		_servoPin2 =servo_pin2;
	}


	_curPos=0;
	_servoPin1Attached=false;
	_servoPin2Attached=false;
}

bool ServoPing::getPingState(){
	return _pingControlsServos;
}

void ServoPing::disablePingControlOfServos(){
	_pingControlsServos=false;
}

void ServoPing::enablePingControlOfServos(){
	_pingControlsServos=true;
}


