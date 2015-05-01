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
#define NOSERVO2 255
#define DEFAULTMINSERVOTHROW 0
#define DEFAULTMINSERVOTHROW 0

class ServoPing {
public:
	ServoPing(uint8_t servoId,uint8_t servo_pin1,uint8_t servo_pin2,uint8_t  ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance,unsigned int rollingAvgCount);
//	ServoPing(uint8_t servo_pin1,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance);
//	ServoPing(uint8_t servo_pin1,uint8_t ping_pin, unsigned int ping_max_cm_distance);
    void disablePingControlOfServos();
    void enablePingControlOfServos();
    bool getPingState();
	unsigned int UpdateCurrentPosition();
	//void

private:
	Servo * _spServo1;
	Servo * _spServo2;
	NewPing * _spSonar;

    unsigned int _curPos;
    unsigned int _RollingPositionAvg;
    unsigned int RollingAveCount;


    unsigned int _servoId;
    unsigned int _maxPingDistance;

    unsigned zeroCount;

    bool _servoPin1Attached;
    unsigned int _servoPin1;
    unsigned int _servo1MinThrow;
    unsigned int _servo1MaxThrow;

    bool _servoPin2Attached;
    unsigned int _servoPin2;
    unsigned int _servo2MinThrow;
    unsigned int _servo2MaxThrow;



    bool _pingControlsServos;
    void commonConstructorRoutines(uint8_t ServoID,uint8_t servo_pin1,uint8_t ping_trigger_pin, uint8_t ping_echo_pin, unsigned int ping_max_cm_distance,unsigned int RollingAvgCount, uint8_t servo_pin2=NOSERVO2 );
};

#endif /* SERVOPING_H_ */
