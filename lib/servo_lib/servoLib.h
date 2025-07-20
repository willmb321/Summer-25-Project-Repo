/*--------------------------------------------------------------------
Name:   William Brown
Date:   5/29/2025
File:   servoLib.h

Purp:  Header file for servo library

Doc:  Prof. Falkinburg - UNL
--------------------------------------------------------------------*/

#ifndef SERVO_H_
#define SERVO_H_
#include <Arduino.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Configures Timer1 for servo use
**/
void servoTimerConfig();

/**
 * Input: char direction
 * Turns servo left, right, or center
 * Waits 500ms time for servo to turn
**/
void turnSetServo(int direction);

/**
 * 
**/
void turnServo(int direction, int mag);

int getOCR1B();


#ifdef __cplusplus
}
#endif

#endif /** SERVO_H_ **/