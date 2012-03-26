/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011/2012. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : gyro.h
  #Author   : Daniel Saul

 */

#ifndef GYRO_H
#define GYRO_H

// Include necessary header files
#include "Arduino.h"
#include "adc.h"

//Declare functions
void setupGyro();

//Declare variables

////////////////////
//Actual functions//
////////////////////

void setupGyro(){
 
    digitalWrite(STATUS_LED,HIGH);
    delay(50);
    digitalWrite(STATUS_LED,LOW);

    if (SERIAL_ENABLED){
        Serial.println("Gyro: Enabled & Calibrated");
    }

}

#endif
