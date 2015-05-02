/*
 * ServoPing.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: Tom Matukas Workshop88 
 */

//#include "ServoPing.h"
//
//
//
//
////ServoPing::ServoPing(uint8_t servoId,uint8_t servo_pin_GameTable, uint8_t servo_pin_LeftArm,uint8_t servo_pin_RightArm, uint8_t ping_trigger_pin, uint8_t ping_echo_pin  ){
////
////		 _servoId=servoId;
////		 _spMinionSonarEyes= new NewPing(ping_trigger_pin,ping_echo_pin, MAX_DISTANCE+10);
////		 _pingControlsServos=true;
////		// _maxPingDistance =MAX_DISTANCE;
////
//////		 _spServoGameTableAxis= new Servo();
//////		 _servoPinGameTable =servo_pin_GameTable;
//////
//////		 _spServoMinionLeftArm= new Servo();
//////		 _servoPinLeftArm =servo_pin_LeftArm;
////
////		 _spServoMinionRightArm= new Servo();
////		 _servoPinRightArm =servo_pin_RightArm;
////
////		 _RollingPositionAvg=0;
////			//_RollingAveCount=	 rollingAvgCount;
////
////		 _curPos=0;
////		 _servosAttached=false;
////
//////		 _servoGameTableMinThrow=0;
//////		 _servoGameTableMaxThrow=120;
//////		 _minionServosArmsMinThrow=0;
//////		 _minionServosArmsMaxThrow=120;
////
////
////	}
////
//	unsigned int ServoPing::UpdateCurrentPosition(){
//
//
//
//	Serial.print(F("S"));
//	Serial.print(_servoId);
//
//	if (_pingControlsServos==false)
//	{
//		Serial.print(F("OFF"));
//		return _spMinionSonarEyes->ping();
//	}
//
//
//	Serial.print(F("ON"));// Every works as long as this line is in. Makes no sense.
//	_curPos =_spMinionSonarEyes->ping();
//
//	_RollingPositionAvg= ((_RollingPositionAvg*_RollingAveCount)+_curPos )/(_RollingAveCount+1);
//
////	_spServoGameTableAxis->write((int) map (_RollingPositionAvg,3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,_servoGameTableMinThrow,_servoGameTableMaxThrow));
////	_spServoMinionLeftArm->write((int) map (_RollingPositionAvg, 3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,_minionServosArmsMinThrow,_minionServosArmsMaxThrow));
//
//	_spServoMinionRightArm->write((int) map (_RollingPositionAvg,3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,0,120));
//
//	Serial.print(_RollingPositionAvg);
//
//	Serial.print (F("--- "));
//	Serial.print(_curPos);
//	return _curPos;
//}
//
//void ServoPing::attachPingAndServo(NewPing & Eyes, Servo & RightArm, unsigned int maxPingDistance)
//{
//	if (_servosandPingAttached)
//	{return;}
//	_maxPingDistance =maxPingDistance;
//	//		 _spServoGameTableAxis->attach(_servoPinGameTable);,
//	//		 _spServoMinionLeftArm->attach(_servoPinLeftArm);
//	         _spMinionSonarEyes = Eyes;
//			_spServoMinionRightArm = RightArm;
//			 _servosandPingAttached=true;
//
//}
//bool ServoPing::MaxDistanceExceeded()
//{
//  if (_curPos>  ( _maxPingDistance * US_ROUNDTRIP_CM))
//		{
//	  	  return true;
//
//		}
//  else
//  {
//	  return false;
//  }
//}
//
//void ServoPing::SetGameTableAxisThrow( unsigned int min, unsigned int max)
//{
//	_servoGameTableMinThrow=min;
//	_servoGameTableMaxThrow=max;
//}
//bool ServoPing::getPingState(){
//	return _pingControlsServos;
//}
//
//void ServoPing::disablePingControlOfServos(){
//	_pingControlsServos=false;
//}
//
//void ServoPing::enablePingControlOfServos(){
//	_pingControlsServos=true;
//}


