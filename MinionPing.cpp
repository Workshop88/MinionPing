// Do not remove the include below
#include "MinionPing.h"
//#include "ServoPing.h"
#include <Servo.h>
#include "NewPing.h"


#define OP_MODE_WAITING_FOR_EVERYONE_TO_WAKE 1
#define OP_MODE_DEMO 2
#define OP_MODE_ACTIVE =3


#define LEFT_MINION_PING_ECHO  2
#define LEFT_MINION_PING_TRIGGER  4  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.

#define LEFT_MINION_TABLE_SERVO 3
#define LEFT_MINION_ARM_LEFTARM_SERVO  5
#define LEFT_MINION_ARM_RIGHTARM_SERVO  6

#define LEFT_MINION_LED 0
#define LEFT_GAME_SERVO_MIN_THROW 30
#define LEFT_GAME_SERVO_MAX_THROW 120



#define RIGHT_MINION_PING_ECHO  7
#define RIGHT_MINION_PING_TRIGGER 8  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define RIGHT_MINION_TABLE_SERVO 9
#define RIGHT_MINION_ARM_LEFTARM_SERVO  10
#define RIGHT_MINION_ARM_RIGHTARM_SERVO  11
#define RIGHT_MINION_LED 12

#define RIGHT_MINION_ID 2
#define RIGHT_GAME_SERVO_MIN_THROW 30
#define RIGHT_GAME_SERVO_MAX_THROW 120


#define DEFAULT_MIN_SERVO_THROW 0
#define DEFAULT_MAX_SERVO_THROW 120
#define MINIONARMMINTHROW 0
#define MINIONARMMAXTHROW  120
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MIN_DISTANCE_TO_ENABLE 10
#define MAX_DISTANCE_TO_DISABLE 60
#define ROLLING_AVG_COUNT 8



//val = analogRead(potpinL);            // reads the value of the potentiometer (value between 0 and 1023)
//  val = map(val, 120, 860, 30, 120);     // scale it to use it with the servo (value between 0 and 180)
//  LeftTableAxis.write(val);                  // sets the servo position according to the scaled value
//  val = analogRead(potpinR);            // reads the value of the potentiometer (value between 0 and 1023)
//  ival=val;
//  val = map(val, 120, 860, 5, 100);     // scale it to use it with the servo (value between 0 and 180)


unsigned int OperationMode=OP_MODE_DEMO;

unsigned int CurLeftPingDistance=0;
unsigned int leftMinionRollingAverage =0;

bool EnableLeftMinion;
Servo LeftMinionRightArm;
Servo LeftMinionLeftArm;
Servo LeftTableAxis;
NewPing  LeftSonarEyes=  NewPing(LEFT_MINION_PING_TRIGGER,LEFT_MINION_PING_ECHO, MAX_DISTANCE+10);



unsigned int CurRightPingDistance=0;
unsigned int rightMinionRollingAverage =0;
//unsigned int previousUs=0;
bool EnableRightMinion;


Servo rightMinionLeftArm;
Servo rightMinionRightArm;
Servo rightTableAxis;
NewPing  rightSonarEyes=  NewPing(RIGHT_MINION_PING_TRIGGER,RIGHT_MINION_PING_ECHO, MAX_DISTANCE+10);




//ServoPing LeftMinion();

//The setup function is called once at startup of the sketch
void setup()
{
	 Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results..
	 pinMode(RIGHT_MINION_LED, OUTPUT);
	 pinMode(LEFT_MINION_LED, OUTPUT);

	 LeftMinionRightArm.attach(LEFT_MINION_ARM_RIGHTARM_SERVO);
	 LeftMinionLeftArm.attach(LEFT_MINION_ARM_LEFTARM_SERVO);
	 LeftTableAxis.attach(LEFT_MINION_TABLE_SERVO);
	 EnableLeftMinion=true;

	 rightMinionLeftArm.attach(RIGHT_MINION_ARM_LEFTARM_SERVO);
	 rightMinionRightArm.attach(RIGHT_MINION_ARM_RIGHTARM_SERVO);
	 rightTableAxis.attach(RIGHT_MINION_TABLE_SERVO);
	 EnableRightMinion=true;


	 }

#define DemoDelay 2000
//#define InThresh 3
//#define DemoDebounce 1500
byte cornersL[4]={50,50,140,140};
byte cornersR[4]={20,80,20,80};

void printCurrentSensorReading()
{
	  char buf[15];
	  sprintf(buf, "L%03d:%03d R%03d:%03d",leftMinionRollingAverage,CurLeftPingDistance,rightMinionRollingAverage,CurRightPingDistance);
	  Serial.println(buf);

}
void updateLeftAndRightMinionPingDistance()
{

	//This separates pinging incase I want to ping on a separate arduino and bring the data over on I2c.
    CurLeftPingDistance =LeftSonarEyes.ping()/US_ROUNDTRIP_CM;
	leftMinionRollingAverage = ((leftMinionRollingAverage *ROLLING_AVG_COUNT)+CurLeftPingDistance)/(ROLLING_AVG_COUNT+1);

	delay(50);// Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings
    CurRightPingDistance =rightSonarEyes.ping()/US_ROUNDTRIP_CM;
	rightMinionRollingAverage = ((rightMinionRollingAverage *ROLLING_AVG_COUNT)+CurRightPingDistance)/(ROLLING_AVG_COUNT+1);
	delay(50);// Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings
}





bool Check2SeeIfBothMinionsHaveFallenASleep()
{
	bool EnterDemoMode =false;

	if (leftMinionRollingAverage>=MAX_DISTANCE_TO_DISABLE || leftMinionRollingAverage==0)
	{
		if (EnableLeftMinion)
		{
			Serial.println("Left Minion is falling asleep");
			EnableLeftMinion=false;

		}

	}
	if (rightMinionRollingAverage>=MAX_DISTANCE_TO_DISABLE || rightMinionRollingAverage==0)
	{
		if (EnableRightMinion)
		{
			Serial.println("Right Minion is falling asleep");
			EnableRightMinion=false;
		}


	}

	if (EnableLeftMinion ==false && EnableRightMinion==false  )
	{
		EnterDemoMode =true;
		printCurrentSensorReading();
		Serial.println("Both minions are asleep. Demo Mode should be enabled");

	}
	return EnterDemoMode;

}

bool checkToSeeIfAMinionhasAwoken()
{
	bool leaveDemoMode =false;
	if (CurLeftPingDistance<MIN_DISTANCE_TO_ENABLE && CurLeftPingDistance>0)
	{
		if (!EnableLeftMinion)
		{
			Serial.println("Left Minion is waking up");

		}
		EnableLeftMinion=true;

	}
	if (CurRightPingDistance<MIN_DISTANCE_TO_ENABLE && CurRightPingDistance>0)
	{
		if(!EnableRightMinion)
		{
			Serial.println("Right Minion is waking up");


		}
		EnableRightMinion=true;

	}

	if (EnableLeftMinion== true || EnableRightMinion==true )
	{
		leaveDemoMode=true;
		printCurrentSensorReading();
		Serial.println("At least one minions has woken up. Leaving Demo Mode");
	}
	return leaveDemoMode;
}
void demoMode()
{
  int i=0;
  Serial.println("Entering Demo Mode");
  while(1){  //don't worry, there's a return in there!
	Serial.print("Position: ");
	Serial.println(i);
	switch (i)
	{
		case 1:
		{
			LeftTableAxis.write((int)cornersL[0]);
			rightTableAxis.write((int)cornersR[0]);
			break;
		}
		case 2:
		{
			LeftTableAxis.write((int)cornersL[1+(i>2)]);
			rightTableAxis.write((int)cornersR[1+(i>2)]);
			break;
		}
		case 3:
		{
		    LeftTableAxis.write((int)cornersL[3]);
		    rightTableAxis.write((int)cornersR[3]);
			break;
		}
		case 4:
		{
		    LeftTableAxis.write((int)cornersL[1+(i<3)]);
		    rightTableAxis.write((int)cornersR[1+(i<3)]);
			break;
		}

	}
	i++;
	if(i >5)
	{
		i=0;
	}
		delay(DemoDelay);
		updateLeftAndRightMinionPingDistance();
		printCurrentSensorReading();
		if (checkToSeeIfAMinionhasAwoken())
		{
			Serial.println("Leaving Demo Mode");
			return;
		}

}//end while 1

}//end demoMode




void testUltrasonicSensors()
{
	updateLeftAndRightMinionPingDistance();
	printCurrentSensorReading();
}



// The loop function is called in an endless loop
void loop()
{



	switch (OperationMode)
	{
	case OP_MODE_WAITING_FOR_EVERYONE_TO_WAKE:
		testUltrasonicSensors();
		break;
	case OP_MODE_DEMO:
		demoMode();
		OperationMode =OP_MODE_WAITING_FOR_EVERYONE_TO_WAKE;// this is just temporary
		break;

	default:
		break;
	}


	updateLeftAndRightMinionPingDistance();
	if (Check2SeeIfBothMinionsHaveFallenASleep())
		{
			OperationMode =OP_MODE_DEMO;
		}
}


//void normalOperation()
//{
//updateLeftAndRightMinionPingDistance();
//
//	    if(( EnableLeftMinion==false)& ( leftMinionRollingAverage< MIN_DISTANCE_TO_ENABLE))
//		{
//			EnableLeftMinion=true;
//		}
//	   // else if (LeftMinionRollingAverage==0)
//	   // {
//	   // 	EnableLeftServos=false;
//	   // }
//
//
//	//	_spServoGameTableAxis->write((int) map (_RollingPositionAvg,3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,_servoGameTableMinThrow,_servoGameTableMaxThrow));
//	//	_spServoMinionLeftArm->write((int) map (_RollingPositionAvg, 3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,_minionServosArmsMinThrow,_minionServosArmsMaxThrow));
//
//		if  (leftMinionRollingAverage >=MAX_DISTANCE_TO_DISABLE )
//			{
//			EnableLeftMinion=false;
//			}
//
//		if (EnableLeftMinion==true)
//		{
//			Serial.print(F("Left Enabled"));
//			LeftMinionRightArm.write((int) map (leftMinionRollingAverage,3, MAX_DISTANCE_TO_DISABLE ,60,90));
//			LeftMinionLeftArm.write((int) map (leftMinionRollingAverage,3, MAX_DISTANCE_TO_DISABLE ,60,90));
//			LeftTableAxis.write((int) map (leftMinionRollingAverage,3, MAX_DISTANCE_TO_DISABLE ,90,0));
//			digitalWrite(LEFT_MINION_LED, HIGH);
//		}
//		else
//		{
//			digitalWrite(LEFT_MINION_LED, LOW);
//			Serial.print(F("Left Disabled"));
//
//		}
//
//
//		Serial.print(leftMinionRollingAverage );
//		Serial.print (F("--- "));
//		Serial.print(CurLeftPingDistance);
//		Serial.println();
//
//		Serial.print ("                                                     ");
//
//
//
//	    if(( EnableRightMinion==false)& ( rightMinionRollingAverage< MIN_DISTANCE_TO_ENABLE))
//		{
//			EnableRightMinion=true;
//		}
//
//
//	//	_spServoGameTableAxis->write((int) map (_RollingPositionAvg,3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,_servoGameTableMinThrow,_servoGameTableMaxThrow));
//	//	_spServoMinionRightArm->write((int) map (_RollingPositionAvg, 3*US_ROUNDTRIP_CM, _maxPingDistance*US_ROUNDTRIP_CM,_minionServosArmsMinThrow,_minionServosArmsMaxThrow));
//
//
//
//		if (EnableRightMinion==true)
//		{
//			Serial.print(F("-- Right Enabled"));
//			rightMinionRightArm.write((int) map (rightMinionRollingAverage,3, MAX_DISTANCE_TO_DISABLE ,60,90));
//			rightMinionLeftArm.write((int) map (rightMinionRollingAverage,3, MAX_DISTANCE_TO_DISABLE ,60,90));
//			rightTableAxis.write((int) map (rightMinionRollingAverage,3, MAX_DISTANCE_TO_DISABLE ,20,100));
//			digitalWrite(RIGHT_MINION_LED, HIGH);
//		}
//		else
//		{
//			digitalWrite(RIGHT_MINION_LED, LOW);
//			Serial.print(F("-- Right Disabled"));
//
//		}
//
//		Serial.print
//		(rightMinionRollingAverage );
//			Serial.print (F("--- "));
//			Serial.println(CurRightPingDistance);
//		if ((EnableLeftMinion==false) & (EnableRightMinion==false))
//			{
//			demoMode();
//			}
//
//
//
//
//}







