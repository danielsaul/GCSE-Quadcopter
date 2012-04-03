*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011/2012. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : accel.h
  #Author   : Daniel Saul

 */


#ifndef ACCEL_H
#define ACCEL_H

#include "Arduino.h"
#include "adc.h"

#define SAMPLECOUNT 400.0
#define XZERO 700
#define YZERO 700
#define ZZERO 700

  
void initializeAccel();
void measureAccel();
void measureAccelSum();
void evaluateMetersPerSec();
void computeAccelBias();

float accelScaleFactor[3] = {0.02395604,0.02395604,0.02395604}; //2.395 = 0.02395604
float runTimeAccelBias[3] = {0, 0, 0};
float accelOneG = 0.0;
float meterPerSecSec[3] = {0.0,0.0,0.0};
long accelSample[3] = {0,0,0};
byte accelSampleCount = 0;



void measureAccel() {

  for (byte axis = XAXIS; axis <= ZAXIS; axis++) {
    const float rawADC = getRawADC(axis);
	if (rawADC > 500) { // Check if measurement good
          
             meterPerSecSec[axis] = rawADC * accelScaleFactor[axis] + runTimeAccelBias[axis];
          
        }
  }
}


void measureAccelSum() {
  for (byte axis = XAXIS; axis <= ZAXIS; axis++) {
    const float rawADC = getRawADC(axis);
    if (rawADC > 500) { // Check if measurement good
	  accelSample[axis] += rawADC;
	}
    
  }
  accelSampleCount++;
  
}

void recalibrateAccel(axis){

    for(int samples = 0; sample < 400; samples++) {
        readADC();
        
        for (byte axis = XAXIS; axis <= ZAXIS; axis++){

            

        }
    }

}


void setupAccel() {

    readADC();
    float adc = getRawADC(axis);

  for (int samples = 0; samples < SAMPLECOUNT; samples++) {
    measureAccelSum();
    delay(10);
  }

  for (byte axis = 0; axis < 3; axis++) {
    meterPerSecSec[axis] = (float(accelSample[axis])/SAMPLECOUNT) * accelScaleFactor[axis];
    accelSample[axis] = 0;
  }
  accelSampleCount = 0;

  runTimeAccelBias[XAXIS] = -meterPerSecSec[XAXIS];
  runTimeAccelBias[YAXIS] = -meterPerSecSec[YAXIS];
  runTimeAccelBias[ZAXIS] = -9.8065 - meterPerSecSec[ZAXIS];

  accelOneG = abs(meterPerSecSec[ZAXIS] + runTimeAccelBias[ZAXIS]);
}



#endif
