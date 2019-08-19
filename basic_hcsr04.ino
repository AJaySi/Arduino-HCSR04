/*
  HC-SR04 Applications:
  1). Detecting objects/obstacles for navigation.
  2). Localization and avoiding/over taking obstacles.
  3). Detecting distance to nearest object.
  4). Parking assist systems and reverse parking.

  Connecting HC-SR04 to arduino:
   HC-SR04 Ultrasonic Module has 4 pins, Ground, VCC, Trig and Echo.
   Ground/GND : Arduino GND
   Power/VCC : 5 volts arduino pin
   Trigger Pin (OUTPUT) : Arduino Digital Pin 9
   Echo Pin (INPUT) : Arduino Digital Pin 10
*/

// Define the Trig and Echo pins as named trigPin and echoPin
const int trigPin = 9;
const int echoPin = 10;


// 'traveltime' stores the roundtrip time for ultra soundwave to return/register to echoPin
long traveltime;
// 'object_distance' stores the distance in cm/inches from the object detected.
unsigned int object_distance;


// Setup and initialise HC-SR04 and all that we need.
void setup()
{
  // Define trigPin as an output, to send out the sound wave.
  pinMode(trigPin, OUTPUT);

  // Define echoPin as input, to receive the echo as input.
  pinMode(echoPin, INPUT);

  // Start the serial monitor, at 9600 baudrate.
  Serial.begin(9600);
}


// Run in Loop
void loop()
{
  unsigned long ret_distance = front_object_distance();
  Serial.println(F("Present Distance to Object is: "));
  Serial.print(ret_distance);
}


// Common function to return distance to object in cms and inches.
float front_object_distance()
{
  // Make sure to set trigPin is clear/LOW State for 5 µs
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  // For generating Ultra sound wave, set 'trigPin' to HIGH State for 10 µs
  // The sensor then creates an 8 cycle burst of ultrasound at 40 kHz
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  // Set trigPin to LOW, to stop sending the sound wave and start/stop the duration to travel back
  digitalWrite(trigPin, LOW);

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
  object_distance = (traveltime * 0.0343) / 2;
  long obj_distanceInch = traveltime * 0.0133 / 2;

  // Default return distance to object in centimeters.
  return object_distance;
}
