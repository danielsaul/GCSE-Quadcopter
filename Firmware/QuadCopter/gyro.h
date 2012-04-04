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

//Declare functions
void calibrateGyro();


//Declare variables
#define GYRO_FACTOR 0.0
float gyroCalibrationSamples[3] = {0.0,0.0,0.0};
float gyroOffset[3] = {0.0,0.0,0.0};

////////////////////
//Actual functions//
////////////////////

void calibrateGyro(){

    for(int samples = 0; samples < 500; samples++){
        readADC();
        for(byte axis = XAXIS; axis <= ZAXIS; axis++){
            float rawADC = getRawADC(axis + 3);
            gyroCalibrationSamples[axis] += rawADC;            
        }
    }

    for byte axis = XAXIS; axis <= ZAXIS; axis++){
        gyroCalibrationSamples[axis] /= 500;
        gyroOffset[axis] *= GYRO_FACTOR;
    }

}


#endif
