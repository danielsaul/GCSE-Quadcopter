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
  
//Declare functions
void measureAccel();
void calibrateAccel();

//Declare variables
#define CONVERSION_FACTOR 0.023956043956
float calibrationSamples[3] = {0.0,0.0,0.0};
float accelOffset[3] = {0.0,0.0,0.0};
float acceleration[3] = {0.0,0.0,0.0};

////////////////////
//Actual functions//
////////////////////

void measureAccel(){

    for(byte axis = XAXIS; axis <= ZAXIS; axis++){
        float rawADC = getRawADC(axis);
        acceleration[axis] = rawADC * CONVERSION_FACTOR + accelOffset[axis];
    }

}

void calibrateAccel(){

    //Take 500 samples and add them together for each axis
    for(int samples = 0; samples < 500; samples++){
        readADC();
        for(byte axis = XAXIS; axis <= ZAXIS; axis++){
            float rawADC = getRawADC(axis);
            calibrationSamples[axis] += rawADC;
        }
    }

    //Divide the sum of the samples by 500, giving an average reading for each axis
    //Then multiply it by the magic number to get the zero offset in metres/sec/sec
    for(byte axis = XAXIS; axis <= ZAXIS; axis++){
        calibrationSamples[axis] /= 500;
        calibrationSamples[axis] *= CONVERSION_FACTOR;
    }

    accelOffset[XAXIS] = -calibrationSamples[XAXIS];
    accelOffset[YAXIS] = -calibrationSamples[YAXIS];
    accelOffset[ZAXIS] = 9.8065-calibrationSamples[ZAXIS];

    

}


#endif
