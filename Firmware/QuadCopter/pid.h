/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : pid.h
  #Author   : Daniel Saul

 */

#ifndef PID_H
#define PID_H

//Include necessary header files
#include "Arduino.h"
#include "QuadCopter.h"

//Declare functions
int processPID(long target, long current);

//Declare Variables
struct PIDvariables{
    int Pgain;
    int Igain;
    int Dgain;
    int previous;
    int prevtime;
    int accumulatedError;
    int Ilimit;
} pidstuff[2] = { 
    { 100, 0.5, 0, 0, 0, 0.0, 500 },
    { 100, 0.5, 0, 0, 0, 0.0, 500 }};

// PID[0]   GYRO_MODE   PITCH
// PID[1]   GYRO_MODE   ROLL




// Proportional Integral Derivative Controller

int processPID(long target, long current, struct PIDvariables *pid){

    int error = target - current;
   // float timediff = (loopTime - prevPID) / 1000000.0; //Convert microseconds to seconds
   // pid->prevtime = loopTime;
    pid->accumulatedError += error;
    //constrain(pid->accumulatedError, -pid->Ilimit, pid->Ilimit);

    int Pterm = (error * pid->Pgain) / 100;
    int Iterm = pid->accumulatedError * pid->Igain;
    int Dterm = ((current - pid->previous) * pid->Dgain) / 100;    
    
    pid->previous = current;

    return Pterm + Iterm + Dterm;

}

#endif
