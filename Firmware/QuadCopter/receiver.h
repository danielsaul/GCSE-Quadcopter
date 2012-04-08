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

//Declare functions
void setupReceiver();
void triggerRX();
void checkMotorArming();

//Declare Variables
int rx_min = 1000;
int rx_centre = 1500;
int rx_max = 2000;
int rx_currentChannel;
int rx_raw[5] = { 1500, 1500, 1000, 1500, 1500 };
long rx_now;
long rx_prev;
unsigned long rx_diff;
bool rx_ready;


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

    rx_now = micros();                                           
    if(rx_prev > 0){                                         
        rx_diff = rx_now - rx_prev;                                
        if(rx_diff > 5000){                                      
            rx_ready = true;                                     
            rx_currentChannel = 0;
        }else if (rx_ready == true){                                  
                if(rx_diff >= 1000 && rx_diff <= 2000){
                    rx_raw[rx_currentChannel] = rx_diff;             
                }
                rx_currentChannel++;                                          }
    }
    
    rx_prev = rx_now;
}

void checkMotorArming(){

        
        if(rx_raw[4] >= rx_max-5 && rx_raw[2] < rx_min+200){                  // Motor Arming
            motorsArmed = true;
        }

        if(rx_raw[4] < rx_max-5){                   // Motor Disarming
            motorsArmed = false;
        }
}

#endif
