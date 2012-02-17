/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : QuadCopter.h
  #Author   : Daniel Saul

 */

#ifndef QUAD_H
#define QUAD_H

/* Pin Definitions */
#define STATUS_LED      13
#define RX_IN           2
#define MOTOR_A         11
#define MOTOR_B         10
#define MOTOR_C         9
#define MOTOR_D         6
#define ULTRASOUND_IN   8
#define ULTRASOUND_OUT  7

/* Serial Communication with Computer - for debugging etc. */
#define BAUD_RATE       115200
#define SERIAL_ENABLED  true

/* Gyro or Gyro&Accel */
#define GYRO_MODE       true
#define MIXED_MODE      false  

/* PID Variables*/
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
//

// Other Variables
bool motorsArmed = false;

#endif
