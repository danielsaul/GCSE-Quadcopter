/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : QuadCopter.pde
  #Author   : Daniel Saul

 */

// Include various header files
#include "QuadCopter.h"
//#include "adc.h"
//#include "pid.h"
#include "receiver.h"
#include <Servo.h>
#include "motors.h"

/////////////////////////////////
// Main Program Initialisation //
// //////////////////////////////
void setup(){

    // Status LED
    pinMode(STATUS_LED, OUTPUT);
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);

    // Begin Serial to Computer, if enabled
    if (SERIAL_ENABLED) {
        Serial.begin(BAUD_RATE);
        Serial.println("Quadcopter - GCSE Electronic Products");
        Serial.println("Daniel Saul - 2012 \n");
    }
    
    setupReceiver();    
    //setupADC();
    //setupGyro();
    setupMotors();
}

void loop(){
   delay(500);

   Serial.print(rx_raw[0]);
   Serial.print(", ");
   Serial.print(rx_raw[1]);
   Serial.print(", ");
   Serial.print(rx_raw[2]);
   Serial.print(", ");
   Serial.print(rx_raw[3]);
   Serial.print(", ");
   Serial.print(rx_raw[4]);
   Serial.println();


}
