/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011/2012. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : QuadCopter.h
  #Author   : Daniel Saul

 */

#ifndef QUAD_H
#define QUAD_H

/* Pin Definitions */
#define STATUS_LED      13
#define RX_IN           2
#define MOTORA_PIN      11
#define MOTORB_PIN      10
#define MOTORC_PIN      9
#define MOTORD_PIN      6
#define ULTRASOUND_IN   8
#define ULTRASOUND_OUT  7
#define BATTERY_READ    0  // Analog 0

/* Serial Communication with Computer - for debugging etc. */
#define BAUD_RATE       115200
#define SERIAL_ENABLED  true

/* Gyro or Gyro&Accel */
#define GYRO_MODE       true
#define MIXED_MODE      false  

// Axis
#define XAXIS           0
#define YAXIS           1
#define ZAXIS           2

// Motors
#define MOTOR_A         0
#define MOTOR_B         1
#define MOTOR_C         2
#define MOTOR_D         3
#define MOTOR_MINSPEED  1000
#define MOTOR_MIDSPEED  1500
#define MOTOR_MAXSPEED  2000
bool motorsArmed =      false;

#endif
