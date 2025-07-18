/*--------------------------------------------------------------------
Name:   William Brown
Date:   5/29/2025   
File:   sensorLib.cpp

Purp:  C file for sensor library

Doc:  Prof. Falkinburg - UNL
--------------------------------------------------------------------*/

#include <Arduino.h>

/**
 * Configures Timer1 for sensor use
**/
void sensorTimerConfig(){
  TCCR1A = 0;                   //Normal mode 0xffff top, rolls over
  TCCR1B = (1 << CS11);         //prescalar 8
  TCCR1C = 0;                   //
  TCNT1H = 0;                   //Set counter to zero, high byte first
  TCNT1L = 0;   

  DDRB |= (1 << PINB1); //set pin to output
  DDRB &= ~(1 << PINB0); //set pin to input
}


/**
 * Triggers ultrasonic senor to send out a burts
 * reads the echo pin pulse
 * converts to inches and returns
**/
double sensorMeasure(){
  sensorTimerConfig();                //Set Timer

  //send trigger
  PORTB |= (1 << PINB1);              //pin high
  delayMicroseconds(10);              //holds for 10us
  PORTB &= ~(1 << PINB1);             //pin low

  //look for and measure echo pulse
  while (!(PINB & (1 << PINB0)));     //wait for echo rising edge
  ICR1 = 0;                           //clear ICR1 and TCNT1
  TCNT1 = 0;
  while (PINB & (1 << PINB0));        //wait for echo falling edge

  //calculate distance
  uint16_t pulse = ICR1;
  double distance = ((pulse*0.5)/148)+1;  //distance in inches, +1 is for width of robot
  
  delay(25);
  return distance;
}

/**
 * Input: double ranges
 * Measures distanst from sensor
 * if it's <= to range return true
 * else return false
**/
boolean checkObject(double range){
    double distance = sensorMeasure();    //get distance
  
    if (distance <= range){               //compare
      return true;
    }
    else{
      return false;
    }
  }