/*--------------------------------------------------------------------
Name:   William Brown
Date:   5/29/2025  
File:   servoLib.cpp

Purp:  C file for servo library

Doc:  Prof. Falkinburg - UNL
--------------------------------------------------------------------*/

#include <Arduino.h>

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
 * Turns servo left, right, or center
 * Waits 500ms time for servo to turn
**/
void turnServo(char* direction){
    servoTimerConfig();           //Set Timer
  
    if (direction == "L"){        //Turn left
      OCR1B = 8;
      delay(500);
    }
    else if(direction == "R"){    //Turn right
      OCR1B = 38;
      delay(500);
    }
    else if(direction == "C"){    //Turn center
      OCR1B = 23;
      delay(500);
    }
}