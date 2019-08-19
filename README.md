HC-SR04 comes complete with ultrasonic transmitter & receiver modules.
The Ranging Distance is around 2cm – 400cms, with Resolution of 0.3cm.

HC-SR04 uses sonar to detect object, using reflected waves,
The time taken between the signal transmission & reception, allows to
calculate the distance to an object.

By measuring time difference between sending & receiving the sound
waves, the distance between the sensor and the object can be calculated.

Note: Speed on sound depends on present temperature and increase
0.6m/s per 1 degress change(wikipedia).
To get accurate readings, knowing temperature with sesnors like BMP280, should be considered.
Calculate speed of sound in m/s: speedofsound = 331.3 + (0.606*temperature) + (0.0124 * humidity);
Humidity impact on speed of sound is negligible

-------
HC-SR04 Applications:
  1). Detecting objects/obstacles for navigation.
  2). Localization and avoiding/over taking obstacles.
  3). Detecting distance to nearest object.
  4). Parking assist systems and reverse parking.
  5). Useable for robots, intruder detection or proximity alarms

------
Connecting HC-SR04 to arduino:
   HC-SR04 Ultrasonic Module has 4 pins, Ground, VCC, Trig and Echo.
   Ground/GND : Arduino GND
   Power/VCC : 5 volts arduino pin
   Trigger Pin (OUTPUT) : Arduino Digital Pin 9
   Echo Pin (INPUT) : Arduino Digital Pin 10

--------------------

This repo contains arudino code for HC-SR04 sesnor for calculating the
distance to the object. There are 2 versions of the libraries used:

1). Using standard libraries, No external dependencies(basic_hcsr04.ino)

2). Using NewPing library (newping_hcsr04.ino)
Prerequired Install: https://playground.arduino.cc/Code/NewPing/
Arduino_IDE: Sketch > Include Library > Add .ZIP Library

3). Compare standard and NewPing library output (compr_std_newping.ino)
This helps decide which library to use, depending on application.


