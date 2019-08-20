#include <NewPing.h>

/*
  The NewPing library written by Tim Eckel provides :
  1. Works with many ultrasonic sensor models: SR04, SRF05, SRF06, DYP-ME007 & Parallax PING
  2. Doesn't lag for a full second if no ping echo is received like all other ultrasonic libraries
  3. Ping sensors consistently and reliably at up to 30 times per second
  4. Timer interrupt method for event-driven sketches
  5. Doesn't use pulseIn, which is slow and gives incorrect results with some ultrasonic sensor models
  ...
*/

// Include the NewPing library. Instructions at https://playground.arduino.cc/Code/NewPing/
#define triggerPinFront 9
#define echoPinFront 10
#define triggerPinBack 11
#define echoPinBack 12
#define MAX_DISTANCE_BACK 250
#define MAX_DISTANCE_FRONT 350

// Constructor: NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]);
// Initializes NewPing to use pin 12(trigger output) and pin 11 for echo input, with max_ping_distance to 350cm
NewPing sonarFront(triggerPinFront, echoPinFront, MAX_DISTANCE_FRONT);
NewPing sonarBack(triggerPinBack, echoPinBack, MAX_DISTANCE_BACK);

float duration, distance;

void setup()
{
  // Start the serial monitor, at 9600 baudrate.
  Serial.begin(9600);
}

void loop()
{
  float backDistance = back_distance();
  Serial.println(F("Back Object distance is: "));
  Serial.print(backDistance);
  Serial.println(" cms");

  float frontDistance = front_distance();
  Serial.println(F("Front object distance is: "));
  Serial.print(frontDistance);
  Serial.println(" cms");
}

// Common function to get the distance to nearest object at the back.
float back_distance()
{
  // Wait 50ms between pings (about 20 pings/sec).
  // 29ms should be the shortest delay between pings.
  delay(500);
  Serial.println(F("#####################################"));
  Serial.println(F("Starting NewPing HC-SR04 measurements"));

  Serial.print("Using sonar.ping_cm: ");
  Serial.print(sonarBack.ping_cm());
  Serial.println("cm");

  duration = sonarBack.ping();
  distance = (duration / 2) * 0.0343;
  Serial.print("Self Calculated: ");
  // Distance will be 0 when out of set max range.
  Serial.print(distance);
  Serial.println(" cms");

  // The ping_median() function takes 'n' duration measurements in a row,
  // throws away the out of range readings and then averages the remaining ones.
  int iterations = 5;
  duration = sonarBack.ping_median(iterations);
  distance = (duration / 2) * 0.0343;
  Serial.print("Median Calculated: ");
  Serial.print(distance);
  Serial.println(" cms");

  // return the median calculated distance from duration.
  return distance;
}

// Common function to get distance to nearest object, in front.
float front_distance()
{
  // Wait 50ms between pings (about 20 pings/sec).
  // 29ms should be the shortest delay between pings.
  delay(500);
  Serial.println(F("#####################################"));
  Serial.println(F("Starting NewPing HC-SR04 measurements"));

  Serial.print("Using sonar.ping_cm: ");
  Serial.print(sonarFront.ping_cm());
  Serial.println("cm");

  duration = sonarFront.ping();
  distance = (duration / 2) * 0.0343;
  Serial.print("Self Calculated: ");
  // Distance will be 0 when out of set max range.
  Serial.print(distance);
  Serial.println(" cms");

  // The ping_median() function takes 'n' duration measurements in a row,
  // throws away the out of range readings and then averages the remaining ones.
  int iterations = 5;
  duration = sonarFront.ping_median(iterations);
  distance = (duration / 2) * 0.0343;
  Serial.print("Median Calculated: ");
  Serial.print(distance);
  Serial.println(" cms");

  //return calculated distance from median duration
  return distance; 
}
