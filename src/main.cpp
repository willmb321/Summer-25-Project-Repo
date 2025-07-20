/*--------------------------------------------------------------------
Name:   William Brown
Date:   7/19/2025   
File:   sensorLib.cpp

Purp:  

Doc:  
--------------------------------------------------------------------*/

#include <Arduino.h>
#include "servoLib.h"
#include "sensorLib.h"


int range = 18;
volatile int servo_direction = -1; // starts going left

/**
 * Servo needs to conituously turn back and forth
 * Sensor scans and checks for object
 *    Performs something if there is an object in range
 * 
**/
void sonarSweep(){
  //Servo sweep logic
  if ((getOCR1B() == 8) || (getOCR1B() == 38)){
    servo_direction*= -1;
  }
  turnServo(servo_direction, 1);

  /*
  //Sensor logic
  if(checkObject(range)){
    Serial.print("Object detected at "); Serial.print(sensorMeasure()); Serial.print(" in!");
    //Add display logic
  }
*/
}

/**
 * Temp function to test servo is working. 
**/
void servoTest(){
  turnServo(-1,1);
}

void setup() {
  Serial.begin(9600);
  Serial.print("Starting up...");
  turnSetServo(-1);
  turnSetServo(0);
  sei();
}

void loop() {
  sonarSweep();

}