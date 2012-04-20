/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011/2012. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : yawhold.h
  #Author   : Daniel Saul

 */

#ifndef YAW_H
#define YAW_H

// Include necessary header files
#include "Arduino.h"

//Declare functions
void processHeadingHold();

//Declare variables
float setHeading = 0;
unsigned long headingTime = micros();

////////////////////
//Actual functions//
////////////////////


#endif
