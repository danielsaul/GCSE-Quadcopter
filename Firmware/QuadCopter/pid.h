/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : receiver.h
  #Author   : Daniel Saul

 */


// Proportional Integral Derivative Controller

void processPID(current, target){

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
