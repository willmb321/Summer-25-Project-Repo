#include <Arduino.h>
#include "servoLib.h"
#include "sensorLib.h"


int range = 18;
volatile int servo_position = 0;
volatile int servo_direction = -1; // starts going left

void setup() {
  Serial.begin(9600);
  Serial.print("Starting up...");
  sei();
}

void loop() {
  //Servo needs to conituously turn back and forth
  //Sensor scans and checks for object
    //Performs something if there is an object in range

  //sonarSweep();
}

void sonarSweep(){
  //Servo sweep logic
  if ((servo_position == 8) || (servo_position == 38)){
    servo_direction*= -1;
  }
  turnServo(servo_direction, 1);

  //Sensor logic
  if(checkObject(range)){
    Serial.print("Object detected at "); Serial.print(sensorMeasure()); Serial.print(" in!");
    //Add display logic
  }
}