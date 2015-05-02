// Do not remove the include below
#include "MinionPing.h"
//#include "ServoPing.h"
#include <Servo.h>
#include "NewPing.h"

#define LEFT_MINION_PING_ECHO  7
#define LEFT_MINION_PING_TRIGGER  8  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define LEFT_MINION_TABLE_SERVO 11
#define LEFT_MINION_ARM_LEFTARM_SERVO  10
#define LEFT_MINION_ARM_RIGHTARM_SERVO  3
#define LEFT_MINION_ID 1
#define LEFT_GAME_SERVO_MIN_THROW 30
#define LEFT_GAME_SERVO_MAX_THROW 120




#define DEFAULT_MIN_SERVO_THROW 0
#define DEFAULT_MAX_SERVO_THROW 120
#define MINIONARMMINTHROW 0
#define MINIONARMMAXTHROW  120
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MIN_DISTANCE_TO_ENABLE 10
#define MAX_DISTANCE_TO_DISABLE 60
#define ROLLING_AVG_COUNT 4



//val = analogRead(potpinL);            // reads the value of the potentiometer (value between 0 and 1023)
//  val = map(val, 120, 860, 30, 120);     // scale it to use it with the servo (value between 0 and 180)
//  myservoL.write(val);                  // sets the servo position according to the scaled value
//  val = analogRead(potpinR);            // reads the value of the potentiometer (value between 0 and 1023)
//  ival=val;
//  val = map(val, 120, 860, 5, 100);     // scale it to use it with the servo (value between 0 and 180)



unsigned int CurLeftPingDistance=0;
unsigned int LeftMinionRollingAverage =0;
unsigned int previousUs=0;
bool EnableLeftServos;
Servo LeftMinionRightArm;
Servo LeftMinionLeftArm;
Servo LeftTableAxis;
NewPing  LeftSonarEyes=  NewPing(LEFT_MINION_PING_TRIGGER,LEFT_MINION_PING_ECHO, MAX_DISTANCE+10);
//ServoPing LeftMinion();

//The setup function is called once at startup of the sketch
void setup()
{
	 Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results..

	 LeftMinionRightArm.attach(LEFT_MINION_ARM_RIGHTARM_SERVO);
	 LeftMinionLeftArm.attach(LEFT_MINION_ARM_LEFTARM_SERVO);
	 LeftTableAxis.attach(LEFT_MINION_TABLE_SERVO);

	 EnableLeftServos=true;
	 //LeftMinion.attachPingAndServo(LeftSonarEyes,LeftMinionRightArm, MAX_DISTANCE);
	 //CurrentDistanceToPingSensor = sp1->UpdateCurrentPosition();
	 //sp1.enablePingControlOfServos();
}

// The loop function is called in an endless loop
void loop()
{
	 delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
	    CurLeftPingDistance =LeftSonarEyes.ping()/US_ROUNDTRIP_CM;
	    LeftMinionRollingAverage = ((LeftMinionRollingAverage *ROLLING_AVG_COUNT)+CurLeftPingDistance)/(ROLLING_AVG_COUNT+1);

	    if(( EnableLeftServos==false)& ( LeftMinionRollingAverage< MIN_DISTANCE_TO_ENABLE))
		{
			EnableLeftServos=true;
		}


	//	_spServoGameTableAxis->write((int) map (_RollingPositionAvg,3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,_servoGameTableMinThrow,_servoGameTableMaxThrow));
	//	_spServoMinionLeftArm->write((int) map (_RollingPositionAvg, 3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,_minionServosArmsMinThrow,_minionServosArmsMaxThrow));

		if  (LeftMinionRollingAverage >=MAX_DISTANCE_TO_DISABLE )
			{
			EnableLeftServos=false;
			}

		if (EnableLeftServos==true)
		{
			Serial.print(F("Left Enabled"));
			LeftMinionRightArm.write((int) map (LeftMinionRollingAverage,3, MAX_DISTANCE_TO_DISABLE ,60,90));
			LeftMinionLeftArm.write((int) map (LeftMinionRollingAverage,3, MAX_DISTANCE_TO_DISABLE ,60,90));
			LeftTableAxis.write((int) map (LeftMinionRollingAverage,3, MAX_DISTANCE_TO_DISABLE ,4,130));
		}
		else
		{
			Serial.print(F("Left Disabled"));

		}



		Serial.print(LeftMinionRollingAverage );
		Serial.print (F("--- "));
		Serial.println(CurLeftPingDistance);


}
