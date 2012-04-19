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
#include "QuadCopter.h"
#include "adc.h"
#include <avr/eeprom.h>

//Declare functions
void setupGyro();
void calibrateGyro();
void measureGyro();

//Declare variables
int gyroCalibrationSamples[3] = {0,0,0};
int gyroOffset[3] = {0,0,0};
float gyroRate[3] = {0.0,0.0,0.0};
float gyroHeading = 0.0;
unsigned long gyroTime = 0;

////////////////////
//Actual functions//
////////////////////

int smooth(int current, int previous, int factor) {
  return ((previous * (16 - factor) + (current * factor))) / 16;
}

void setupGyro(){

    gyroOffset[XAXIS] = eeprom_read_word((uint16_t*)EEPROM_GYROZEROX);
    gyroOffset[YAXIS] = eeprom_read_word((uint16_t*)EEPROM_GYROZEROY);
    gyroOffset[ZAXIS] = eeprom_read_word((uint16_t*)EEPROM_GYROZEROZ);

    if (SERIAL_ENABLED){
        Serial.println("Gyro: Enabled.");
    }

}

void measureGyro(){

    for(byte axis = XAXIS; axis <= ZAXIS; axis++){
        int rawADC = getRawADC(axis + 3);
        rawADC -= gyroOffset[axis];
       // gyroRate[axis] = smooth(rawADC, gyroRate[axis], 8);
        gyroRate[axis] = rawADC * radians((3.3/4095.0) / 0.002);
    }

// Get heading from the Z axis of the gyro
  long int currentTime = micros();
  if (gyroRate[ZAXIS] > radians(1.0) || gyroRate[ZAXIS] < radians(-1.0)) {
    gyroHeading += gyroRate[ZAXIS] * ((currentTime - gyroTime) / 1000000.0);
  }
  gyroTime = currentTime;


}

void calibrateGyro(){

    for(int samples = 0; samples < 500; samples++){
        readADC();
        for(byte axis = XAXIS; axis <= ZAXIS; axis++){
            int rawADC = getRawADC(axis + 3);
            gyroCalibrationSamples[axis] += rawADC;            
        }
    }

    for(byte axis = XAXIS; axis <= ZAXIS; axis++){
        gyroOffset[axis] = gyroCalibrationSamples[axis] / 500;
    }

    eeprom_write_word((uint16_t*)EEPROM_GYROZEROX, gyroOffset[XAXIS]); 
    eeprom_write_word((uint16_t*)EEPROM_GYROZEROY, gyroOffset[YAXIS]); 
    eeprom_write_word((uint16_t*)EEPROM_GYROZEROZ, gyroOffset[ZAXIS]); 

    if (SERIAL_ENABLED){
        Serial.println("Gyroscopes: Calibrated & Saved.");
    }

}


#endif
