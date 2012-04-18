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
    float Pgain;
    float Igain;
    float Dgain;
    float previous;
    float prevtime;
    float accumulatedError;
    float Ilimit;
} pidstuff[7] = { 
    { 100.0, 0.0, -300.0, 0.0, 0.0, 0.0, 1000 }, //PID[0]  GYRO_MODE  ROLL
    { 100.0, 0.0, -300.0, 0.0, 0.0, 0.0, 1000 }, //PID[1]  GYRO_MODE  PITCH
    { 200.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1000 }, //PID[2]  GYRO_MODE  YAW
    { 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.375 }, //PID[3]  STABLE     ROLL
    { 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.375 }, //PID[4]  STABLE     PITCH
    { 100.0, 0.0, -300.0, 0.0, 0.0, 0.0, 1000 }, //PID[5]  STABLEGYRO ROLL
    { 100.0, 0.0, -300.0, 0.0, 0.0, 0.0, 1000 }};//PID[6]  STABLEGYRO PITCH
    { 3.0, 0.1, 0.0, 0.0, 0.0, 0.0, 1000 }};//PID[7]  HEADING HOLD




// Proportional Integral Derivative Controller

int processPID(long target, long current, struct PIDvariables *pid){

    float error = target - current;

    float timediff = (loopTime - pid->prevtime) / 1000000.0; //Convert microseconds to seconds
    pid->prevtime = loopTime;

    pid->accumulatedError += error * timediff;
    constrain(pid->accumulatedError, -pid->Ilimit, pid->Ilimit);

    int Pterm = error * pid->Pgain;
    int Iterm = pid->accumulatedError * pid->Igain;
    int Dterm = ((current - pid->previous) * pid->Dgain) / (timediff * 100);    
    
    pid->previous = current;

    return Pterm + Iterm + Dterm;

}

void zeroAccumulatedError(){
    for(byte i = 0; i <= 6; i++){
        pidstuff[i].accumulatedError = 0;
        pidstuff[i].prevTime = current;
    }
}

#endif
