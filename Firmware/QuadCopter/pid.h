/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : receiver.h
  #Author   : Daniel Saul

 */

#ifndef PID_H
#define PID_H

//Include necessary header files
#include "Arduino.h"
#include "QuadCopter.h"

//Declare functions
int processPID(current, target);

//Declare Variables
struct PIDvariables{
    float Pgain;
    float Igain;
    float Dgain;
    float previous;
    float prevtime;
    float accumulatedError;
    float windupGuard;
} ;

PIDvariables PID[10];

// PID[1]   GYRO_MODE   PITCH
// PID[2]   GYRO_MODE   ROLL
// PID[3]   MIXED_MODE  PITCH
// PID[4]   MIXED_MODE  ROLL
// PID[5]   MIXED_MODE  GYROPITCH
// PID[6]   MIXED_MODE  GYROROLL
// PID[7]   HEADING
// PID[8]   ALTITUDE


// Proportional Integral Derivative Controller

int processPID(current, target){

    error = target - current;
    float timediff = (loopTime - prevPID) / 1000000.0; //Convert microseconds to seconds
    prevPID = loopTime;
    PID_accumulatedError += timediff * error;
    
    float Pterm = error * PID_Pgain;
    float Iterm = PID_accumulatedError * PID_Igain;
    float Dterm = (((current - PID_prevpos) / timediff) * PID_Dgain) / 100;    
    
    PID_prevpos = current;

    return Pterm + Iterm + Dterm;

}

#endif
