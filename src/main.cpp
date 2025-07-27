/*--------------------------------------------------------------------
Name:   William Brown
Date:   7/19/2025   
File:   main.cpp

Purp:  

Doc:  
--------------------------------------------------------------------*/

#include <Arduino.h>
#include "servoLib.h"
#include "sensorLib.h"


int range = 18;
boolean object = false;
volatile int first_sight = -1;
volatile int end_sight = -1;
volatile double distance = 0;
volatile int servo_direction = -1; // starts going left

/**
 * Sends notification to terminal and screen in case of object
 * 
**/
void notifyLogic(double location, double distance){
  Serial.print("Object detected at "); Serial.print(location); Serial.print(" and "); Serial.print(distance); Serial.print(" in!");
  Serial.println();
}

/**
 * Servo needs to conituously turn back and forth
 * Sensor scans and checks for object
 *    Check if same object then
 *    Performs something if there is an object in range
 * 
**/
void sonarSweep(){
  //Servo sweep logic
  if ((getOCR1B() == 8) || (getOCR1B() == 38)){
    servo_direction*= -1;
  }
  turnServo(servo_direction, 1);

  
  //Sensor logic
  //Need to find center of object
  if((checkObject(range)) && (first_sight == -1)){ //If object is detected and first_sight not recorded
    first_sight = OCR1B;
    distance = sensorMeasure();
  }
  else if(!(checkObject(range)) && (first_sight != -1)){ //If object not detected and first_sight is recorded
    end_sight = OCR1B;
  }
  if((first_sight != -1) && (end_sight != -1)){ //Check for complete object
    object = true;
    notifyLogic((first_sight+end_sight)/2, distance);
    object = false;
    first_sight = -1;
    end_sight = -1;
  }
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
  turnSetServo(1);
  Serial.println();
  sei();
}

void loop() {
  sonarSweep();
}