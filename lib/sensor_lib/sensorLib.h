/*--------------------------------------------------------------------
Name:   William Brown
Date:   5/29/2025  
File:   sensorLib.h

Purp:  Header file for sensor library

Doc:  Prof. Falkinburg - UNL
--------------------------------------------------------------------*/

#ifndef SENSOR_H_
#define SENSOR_H_
#include <Arduino.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Configures Timer1 for sensor use
**/
void sensorTimerConfig();

/**
 * Triggers ultrasonic senor to send out a burts
 * reads the echo pin pulse
 * converts to inches and returns
**/
double sensorMeasure();

/**
 * Input: double ranges
 * Measures distanst from sensor
 * if it's <= to range return true
 * else return false
**/
boolean checkObject(double range);


#ifdef __cplusplus
}
#endif

#endif /** SENSOR_H_ **/