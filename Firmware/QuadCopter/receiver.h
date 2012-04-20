/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011/2012. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : receiver.h
  #Author   : Daniel Saul

 */

#ifndef RECEIVER_H
#define RECEIVER_H

// Include necessary header files
#include "Arduino.h"
#include "QuadCopter.h"
#include "gyro.h"
#include "accel.h"

//Declare functions
void setupReceiver();
void triggerRX();
void checkRXCommands();

//Declare Variables
int rxCurrentChannel;
int rxRaw[5] = { 1500, 1500, 1000, 1500, 1500 };
long rxNow;
long rxPrev;
unsigned long rxDiff;
bool rxReady = false;


// Channels:
// 0. Pitch         (Forward/backward)
// 1. Roll          (Left/Right)
// 2. Throttle      (Up/Down)
// 3. Yaw           (Spin Left/Right)
// 4. Motor Arming

////////////////////
//Actual functions//
////////////////////

void setupReceiver(){

    pinMode(RX_IN, INPUT);                       // Set the pin as input
    attachInterrupt(0,triggerRX,RISING);       // Interrupt on receiver pin for when it goes from low to HIGH
   
    digitalWrite(STATUS_LED,HIGH);              //Flash Status LED
    delay(50);
    digitalWrite(STATUS_LED,LOW);

    if (SERIAL_ENABLED){
        Serial.println("Receiver: Enabled.");
    }

}

void triggerRX(){

    rxNow = micros();                                           
    if(rxPrev > 0){                                         
        rxDiff = rxNow - rxPrev;                                
        if(rxDiff > 5000){                                      
            rxReady = true;                                     
            rxCurrentChannel = 0;
        }else if (rxReady == true){                                  
                if(rxDiff >= 1000 && rxDiff <= 2000){
                    rxRaw[rxCurrentChannel] = rxDiff;             
                }
                rxCurrentChannel++;                                          
        }
    }
    
    rxPrev = rxNow;
}

void checkRXCommands(){

        // Motor Arming
        if(rxRaw[4] >= RX_MAX-5 && rxRaw[2] < RX_MIN+200 && !motorsArmed){
            motorsArmed = true;
            digitalWrite(STATUS_LED, HIGH);
            zeroAccumulatedError(); 
            if(SERIAL_ENABLED){
                Serial.println("Motors: Armed.");
            }
        }

        // Motor Disarming
        if(rxRaw[4] < RX_MAX-5 && motorsArmed){                   
            motorsArmed = false;
            digitalWrite(STATUS_LED, LOW);
            zeroAccumulatedError();
            if(SERIAL_ENABLED){
                Serial.println("Motors: Disarmed.");
            }
        }

    // Sensor Calibration
    if(!motorsArmed && rxRaw[2] < RX_MIN+100 && rxRaw[3] < RX_MIN+100 && rxRaw[0] < RX_MIN+100 && rxRaw[1] > RX_MAX-100){
        zeroAccumulatedError();
        calibrateGyro();
        calibrateAccel();
    }
}



#endif
