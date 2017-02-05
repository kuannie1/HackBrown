/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <Wire.h>
#include <SparkFun_VL6180X.h>
// twelve servo objects can be created on most boards
Servo horServ;  // horizontal, pan
Servo vertServ; // vertical, tilt

#define VL6180X_ADDRESS 0x29
VL6180xIdentification identification;
VL6180x sensor(VL6180X_ADDRESS);


int pos = 0;    // variable to store the servo position

// storing servo positions
float horPos = 0;
float vertPos = 0;

int stopSignal = 0; // variable that notifies you whether to stop
int finishVar = 0;


void setup() {
  
  horServ.attach(9);  // attaches the servo on pin 9 to the servo object
  vertServ.attach(10); // attaches the servo on pin 10 to the servo object

  //Start serial port:
  Serial.begin(9600); // Start Serial at 9600bps
  Wire.begin(); //Start 12C library
  delay(100);

  if (sensor.VL6180xInit() != 0) {
    Serial.println("FAILED TO INITIALIZE"); // Initialize device and check for errors
  };
  sensor.VL6180xDefautSettings(); // load default settings to get started.

  delay(1000); // delay 1s
}

void loop() {
  bool Dir = true;
  // initializing a variable to determine direction
  if (finishVar == 0) {
    for (vertPos = 0; vertPos <= 30; vertPos += 3) {
      //vertical (phi) angle from 0 to 30 increment by 1
      vertServ.write(vertPos); // write to vertical servo
      pan(Dir);
      // run the horizontal servo cunction that takes in direction
      Dir = !Dir;
    }
  }
  finishVar = 1;
  // once the vertical position reaches 30, the finish variable is 1 and will stop taking data
}

void pan(bool Dir) {
  int stepsize = 1;
  int start = 45;
  int end = 135;
  int avg;
  if (Dir == false) {
    for (pos = start; pos <= end; pos += stepsize) { // goes from 0 degrees to 180 degrees
      // in steps of 5 degrees
      horServ.write(pos);              // tell servo to go to position in variable 'pos'

      //obtain IR data
      unsigned long count = 0;
      // initialize a variable count to take an average
      //Get Distance and report in mm
      Serial.print(sensor.getDistance()); 
      Serial.print(", ");
      Serial.print(pos);
      Serial.print(", ");
      Serial.println(vertPos);
      // print to serial monitor the vertical angle, horizontal angle, IR average
      delay(10);                       // waits 10ms for the servo to reach the position
    }
  }
  if (Dir == true) {
      // in steps of 1 degree
      horServ.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 10ms for the servo to reach the position
    }
  }
