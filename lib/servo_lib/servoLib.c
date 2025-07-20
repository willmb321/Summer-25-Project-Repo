/*--------------------------------------------------------------------
Name:   William Brown
Date:   5/29/2025  
File:   servoLib.cpp

Purp:  C file for servo library

Doc:  Prof. Falkinburg - UNL
--------------------------------------------------------------------*/

#include <Arduino.h>

volatile int OCR1B_var = 23; // Used to keep track of previous position

/**
 * Configures Timer1 for servo use
**/
void servoTimerConfig(){
  cli();                            // Disable global interrupts
  EIMSK = 0;                        // Disable INT0
  EIFR = 0;                         // Clear pending INT0 interrupt
  EICRA = 0;                        // Clear Everything!!!!!!!!!!!
  TCCR1A = 0, TCCR1B = 0, TCCR1C = 0;
  TCNT1 = 0;
  OCR1A = 0, OCR1B = 0;
  sei();                            // Re-enable global interrupts

  DDRB |= (1 << PINB2);                                                 //set to output
  TCCR1A = (1 << COM1B1) | (1 << WGM11) | (1 << WGM10);                 //PWM, top at 0x03FF
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10);     //CTC immediate, 1024 prescaler
  OCR1A = 313;                                                          // gives a period of 20ms
}

/**
 * Input: char direction
 * Turns servo left(-1), right(1), or center(0)
 * Waits 500ms time for servo to turn
**/
void turnSetServo(int direction){
    servoTimerConfig();           //Set Timer
  
    if (direction == -1){        //Turn left
      OCR1B = 8;
      delay(500);
    }
    else if(direction == 1){    //Turn right
      OCR1B = 38;
      delay(500);
    }
    else if(direction == 0){    //Turn center
      OCR1B = 23;
      delay(500);
    }
}

void turnServo(int direction, int mag){
  servoTimerConfig();
  OCR1B = OCR1B_var;
  
  if ((direction == -1) && (OCR1B > 8)){
    OCR1B--;
    OCR1B_var = OCR1B;
    delay(100);
  }
  else if ((direction == 1)  && (OCR1B < 38)){
    OCR1B++;
    OCR1B_var = OCR1B;
    delay(100);
  }
}

int getOCR1B(){
  return OCR1B;
}