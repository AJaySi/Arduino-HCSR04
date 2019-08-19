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
#include <NewPing.h>

// Define distance to detect objects within this limit. [default = 500cm]
const int triggerPin 12;
const int echoPin 11;
#define MAX_DISTANCE 350

// Constructor: NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]);
// Initializes NewPing to use pin 12(trigger output) and pin 11 for echo input, with max_ping_distance to 350cm
NewPing sonar(triggerPin, ehcoPin, MAX_DISTANCE);

float duration, distance;

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting NewPing HC-SR04 measurements");
}


void loop()
{
    // Wait 50ms between pings (about 20 pings/sec). 
    // 29ms should be the shortest delay between pings.
    delay(50);
    
    Serial.print("Using sonar.ping_cm: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
    
    Serial.print("Using sonar.ping_in: ");
    Serial.print(sonar.ping_in());
    Serial.println("inches");
    
    duration = sonar.ping();
    distance = (duration / 2) * 0.0343;
    Seiral.print("Self Calculated: ");
    // Distance will be 0 when out of set max range.
    Serial.print(distance);
    Serial.println(" cms");
    
    // The ping_median() function takes 'n' duration measurements in a row, 
    throws away the out of range readings and then averages the remaining ones.
    int iterations = 5;
    duration = sonar.ping_median(iterations);
    distance = (duration / 2) * 0.0343;
    Seiral.print("Median Calculated: ");
    Serial.print(distance);
    Serial.println(" cms");
    
}
