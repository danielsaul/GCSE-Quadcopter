/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011/2012. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : motors.h
  #Author   : Daniel Saul

 */

#ifndef MOTORS_H
#define MOTORS_H

// Include necessary header files
#include "Arduino.h"
#include "QuadCopter.h"
#include <Servo.h>


//Declare functions
void setupMotors();
void updateMotors();

//Declare Variables
Servo motorA;
Servo motorB;
Servo motorC;
Servo motorD;

int motorSpeed[4] = { MOTOR_MINSPEED, MOTOR_MINSPEED, MOTOR_MINSPEED, MOTOR_MINSPEED };

////////////////////
//Actual functions//
////////////////////

void setupMotors(){

    motorA.attach(MOTORA_PIN);
    motorB.attach(MOTORB_PIN);
    motorC.attach(MOTORC_PIN);
    motorD.attach(MOTORD_PIN);

    digitalWrite(STATUS_LED,HIGH);              //Flash Status LED
    delay(50);
    digitalWrite(STATUS_LED,LOW);

    updateMotors();
        
    if (SERIAL_ENABLED){
        Serial.println("Motors: Setup Complete.");
        Serial.println("Motors: Disarmed.");
    }

}

void updateMotors(){

    motorA.writeMicroseconds(motorSpeed[MOTOR_A]);
    motorB.writeMicroseconds(motorSpeed[MOTOR_B]);
    motorC.writeMicroseconds(motorSpeed[MOTOR_C]);
    motorD.writeMicroseconds(motorSpeed[MOTOR_D]);

}


#endif
