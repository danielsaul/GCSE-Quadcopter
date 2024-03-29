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

// Axis
#define XAXIS           0
#define YAXIS           1
#define ZAXIS           2

// Motors
#define MOTOR_A         0
#define MOTOR_B         1
#define MOTOR_C         2
#define MOTOR_D         3
#define MOTOR_OFFSPEED  1000
#define MOTOR_MINSPEED  1100
#define MOTOR_MIDSPEED  1500
#define MOTOR_MAXSPEED  2000
bool motorsArmed =      false;
float rollAxis = 0.0;
float pitchAxis = 0.0;
float yawAxis = 0.0;

// RX
#define RX_MIN          1000
#define RX_MAX          2000
#define RX_CENTRE       1500

// EEPROM Addresses
#define EEPROM_GYROZEROX    0
#define EEPROM_GYROZEROY    2
#define EEPROM_GYROZEROZ    4
#define EEPROM_ACCELZEROX   6
#define EEPROM_ACCELZEROY   8
#define EEPROM_ACCELZEROZ   10

// General variables

unsigned long loopTime = 0;
unsigned long prevTime = 0;
unsigned long diffTime = 0;
float diffTimeSecs = 0.001;

#endif
