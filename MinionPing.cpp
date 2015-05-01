// Do not remove the include below
#include "MinionPing.h"
#include "ServoPing.h"
#include "NewPing.h"

#define LEFT_MINION_PING_ECHO  7
#define LEFT_MINION_PING_TRIGGER  8  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define LEFT_MINION_ARM_SERVOS  3
#define LEFT_MINION_TABLE_SERVO 10
#define LEFT_MINION_ID 1
#define MAX_DISTANCE 30 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define ROLLING_AVG_COUNT 5000
ServoPing *sp1;

unsigned int CurrentDistanceToPingSensor=0;
unsigned int RollingAverage =0;
unsigned int previousUs=0;




//The setup function is called once at startup of the sketch
void setup()
{
	 Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results..

	 sp1= new ServoPing(LEFT_MINION_ID, LEFT_MINION_ARM_SERVOS,LEFT_MINION_TABLE_SERVO,LEFT_MINION_PING_TRIGGER,LEFT_MINION_PING_ECHO,MAX_DISTANCE, ROLLING_AVG_COUNT);
	 sp1->disablePingControlOfServos();
	 //CurrentDistanceToPingSensor = sp1->UpdateCurrentPosition();
	 //sp1.enablePingControlOfServos();
}

// The loop function is called in an endless loop
void loop()
{
	 delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
	 CurrentDistanceToPingSensor = sp1->UpdateCurrentPosition()/  US_ROUNDTRIP_CM;

	  if ((sp1->getPingState()==false)& ((CurrentDistanceToPingSensor>0) & (CurrentDistanceToPingSensor<=5)))
	 {
		  sp1->enablePingControlOfServos();

	 }
	  //if (previousUs!=CurrentDistanceToPingSensor)
	  //{
	  Serial.print(F("(Ping: "));

	  Serial.print(CurrentDistanceToPingSensor);
	  Serial.println( F("Distance to sensor"));

	  previousUs= CurrentDistanceToPingSensor;
	  if (CurrentDistanceToPingSensor> 40)
	  {
		  sp1->disablePingControlOfServos();
	  }


}
