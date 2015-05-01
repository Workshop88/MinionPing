// Do not remove the include below
#include "MinionPing.h"
#include "ServoPing.h"
#include "NewPing.h"

#define LEFT_MINION_PING_TRIGGER  1  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define LEFT_MINION_PING_ECHO  0
#define LEFT_MINION_ARM_SERVOS  2
#define LEFT_MINION_TABLE_SERVO 4

#define MAX_DISTANCE 150 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

ServoPing sp1(LEFT_MINION_ARM_SERVOS,LEFT_MINION_TABLE_SERVO,LEFT_MINION_PING_TRIGGER,LEFT_MINION_PING_ECHO,MAX_DISTANCE);
unsigned int uS=0;
unsigned int previousUs=0;





//The setup function is called once at startup of the sketch
void setup()
{
	 Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

}

// The loop function is called in an endless loop
void loop()
{
	 delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
	 //Serial.print("Just before update position");
	 uS = sp1.UpdateCurrentPosition();
	 //uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).

	  //if (previousUs!=uS)
	  //{
	  Serial.print("Ping: ");
	  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
	  Serial.print("cm ");
	  Serial.print(uS);
	  Serial.println("uSeconds");
	  //}
	  previousUs= uS;
}
