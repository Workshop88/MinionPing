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


//
//class ServoPing {
//public:
//	ServoPing();
//
//	void attachPingAndServo(NewPing* Eyes, Servo* RightServo,unsigned int MaxPingDistance );
////	ServoPing(uint8_t servo_pin1,uint8_t ping_pin, unsigned int ping_max_cm_distance);
//    void disablePingControlOfServos();
//    void enablePingControlOfServos();
//    bool getPingState();
//    bool MaxDistanceExceeded();
//	unsigned int UpdateCurrentPosition();
//	void SetGameTableAxisThrow(unsigned int min, unsigned int max);
//    void AttachServos();
//
//private:
////	Servo * _spServoGameTableAxis;
////	Servo * _spServoMinionLeftArm;
//	Servo * _spServoMinionRightArm;
//	NewPing * _spMinionSonarEyes;
//
//    unsigned int _curPos;
//    unsigned int _RollingPositionAvg;
//    unsigned int _RollingAveCount;
//
//
//    unsigned int _servoId;
//    unsigned int _maxPingDistance;
//
//    //unsigned zeroCount;
//
//    bool _servosandPingAttached;
//    unsigned int _servoPinGameTable;
//    unsigned int _servoGameTableMinThrow;
//    unsigned int _servoGameTableMaxThrow;
//
//
////    unsigned int _minionServosArmsMinThrow;
////    unsigned int _minionServosArmsMaxThrow;
//
//
//    unsigned int _servoPinLeftArm;
//    unsigned int _servoPinRightArm;
//
//
//
//    bool _pingControlsServos;
//
//};

#endif /* SERVOPING_H_ */
