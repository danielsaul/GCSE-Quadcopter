/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011/2012. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : accel.h
  #Author   : Daniel Saul

 */

#ifndef ACCEL_H
#define ACCEL_H

// Include necessary header files
#include "Arduino.h"
#include "QuadCopter.h"
#include "adc.h"
#include <avr/eeprom.h>
#include "fourthorderfilter.h"
  
//Declare functions
void setupAccel();
void measureAccel();
void calibrateAccel();

//Declare variables
#define CONVERSION_FACTOR 0.023956043956
float accelCalibrationSamples[3] = {0.0,0.0,0.0};
float accelOffset[3] = {0.0,0.0,0.0};
float acceleration[3] = {0.0,0.0,0.0};
float filteredAccel[3] = {0.0,0.0,0.0};

////////////////////
//Actual functions//
////////////////////

void setupAccel(){

    accelOffset[XAXIS] = eeprom_read_word(EEPROM_ACCELZEROX);
    accelOffset[YAXIS] = eeprom_read_word(EEPROM_ACCELZEROY);
    accelOffset[ZAXIS] = eeprom_read_word(EEPROM_ACCELZEROZ);

    setupFourthOrder();

    if (SERIAL_ENABLED){
        Serial.println("Accel: Enabled.");
    }

}


void measureAccel(){

    for(byte axis = XAXIS; axis <= ZAXIS; axis++){
        float rawADC = getRawADC(axis);
        acceleration[axis] = rawADC * CONVERSION_FACTOR + accelOffset[axis];
        filteredAccel[axis] = computeFourthOrder(acceleration[axis], &fourthOrder[axis]);
    }

}

void calibrateAccel(){

    //Take 500 samples and add them together for each axis
    for(int samples = 0; samples < 500; samples++){
        readADC();
        for(byte axis = XAXIS; axis <= ZAXIS; axis++){
            float rawADC = getRawADC(axis);
            accelCalibrationSamples[axis] += rawADC;
        }
    } 

    //Divide the sum of the samples by 500, giving an average reading for each axis
    //Then multiply it by the magic number to get the zero offset in metres/sec/sec
    for(byte axis = XAXIS; axis <= ZAXIS; axis++){
        accelCalibrationSamples[axis] /= 500;
        accelCalibrationSamples[axis] *= CONVERSION_FACTOR;
    }

    accelOffset[XAXIS] = -accelCalibrationSamples[XAXIS];
    accelOffset[YAXIS] = -accelCalibrationSamples[YAXIS];
    accelOffset[ZAXIS] = 9.8065-accelCalibrationSamples[ZAXIS];

    eeprom_update_word(EEPROM_ACCELZEROX, accelOffset[XAXIS]);
    eeprom_update_word(EEPROM_ACCELZEROY, accelOffset[YAXIS]);
    eeprom_update_word(EEPROM_ACCELZEROZ, accelOffset[ZAXIS]);

    if (SERIAL_ENABLED){
        Serial.println("Accelerometer: Calibrated & Saved.");
    }

}


#endif
