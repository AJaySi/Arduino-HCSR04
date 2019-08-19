/*
  Example program to show the comparison of results from standard and NewPing Library.

  Connecting HC-SR04 to arduino:
   HC-SR04 Ultrasonic Module has 4 pins, Ground, VCC, Trig and Echo.
   Ground/GND : Arduino GND
   Power/VCC : 5 volts arduino pin
   Trigger Pin (OUTPUT) : Arduino Digital Pin 9
   Echo Pin (INPUT) : Arduino Digital Pin 10
*/

// Include the NewPing library. Instructions at https://playground.arduino.cc/Code/NewPing/
#include <NewPing.h>
#define MAX_DISTANCE 350

// Define the Trig and Echo pins as named trigPin and echoPin
const int triggerPin = 9;
const int echoPin = 10;

// 'traveltime' stores the roundtrip time for ultra soundwave to return/register to echoPin
long traveltime;
// 'object_distance' stores the distance in cm/inches from the object detected.
long object_distance;

// Constructor: NewPing sonar(triggerPin, echoPin [, max_cm_distance]);
// Initializes NewPing to use pin 12(trigger output) and pin 11 for echo input, with max_ping_distance to 350cm
NewPing sonar(triggerPin, echoPin, MAX_DISTANCE);


// Setup and initialise HC-SR04 and all that we need.
void setup()
{
  // Define trigPin as an output, to send out the sound wave.
  pinMode(triggerPin, OUTPUT);

  // Define echoPin as input, to receive the echo as input.
  pinMode(echoPin, INPUT);

  // Start the serial monitor, at 9600 baudrate.
  Serial.begin(9600);
}


// Run in Loop
void loop()
{
  float ret_distance = front_object_distance();
  Serial.println(F("Present Distance to Object is: "));
  Serial.print(ret_distance);
  Serial.println(" cms");

  delay(500);

  float ret_distance_np = front_object_distance_NP();
  Serial.println(F("Starting NewPing HC-SR04 measurements: "));
  Serial.print(ret_distance_np);
  Serial.println(" cms");

  Serial.println("#################################");
}


// Common function to return distance to object in cms and inches.
float front_object_distance()
{
  // Make sure to set trigPin is clear/LOW State for 5 µs
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);

  // For generating Ultra sound wave, set 'trigPin' to HIGH State for 10 µs
  // The sensor then creates an 8 cycle burst of ultrasound at 40 kHz
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  // Set trigPin to LOW, to stop sending the sound wave and start/stop the duration to travel back
  digitalWrite(triggerPin, LOW);

  /*
    When sound waves reach receiver, it turns the echoPin HIGH for the same duration.
    pulseIn(), function waits for echoPin to go into HIGH and then stops timing when it switches to LOW state.
    Read in the echoPin input, as the roundtrip duration for ultra sound wave to reach back from detected object.
  */
  traveltime = pulseIn(echoPin, HIGH);

  /*
    Let 'd' be the distance, and speed of sound as 343 m/s Or 0.034cm/µs, there distance will equal
    duration multiplied by speed of sound. As the sound wave has to travel to the object and back to
    the sensor echoPin, we need to only consider half the duration to obect in front.
    distance to object = (traveltime/2) x speed of sound
  */
  object_distance = (traveltime * 0.034) / 2;
  long obj_distanceInch = traveltime * 0.0133 / 2;

  // Default return distance to object in centimeters.
  return object_distance;
}


float front_object_distance_NP()
{
  // Wait 50ms between pings (about 20 pings/sec).
  // 29ms should be the shortest delay between pings.
  delay(50);
  long duration, distance;

  Serial.print("Using sonar.ping_cm: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");

  //Serial.print("Using sonar.ping_in: ");
  //Serial.print(sonar.ping_in());
  //Serial.println("inches");

  duration = sonar.ping();
  distance = (duration / 2) * 0.0343;
  Serial.print("Self Calculated: ");
  // Distance will be 0 when out of set max range.
  Serial.print(distance);
  Serial.println(" cms");

  // The ping_median() function takes 'n' duration measurements in a row,
  // throws away the out of range readings and then averages the remaining ones.
  int iterations = 5;
  duration = sonar.ping_median(iterations);
  distance = (duration / 2) * 0.0343;
  Serial.print("Median Calculated: ");
  Serial.print(distance);
  Serial.println(" cms");

  return distance;
}
