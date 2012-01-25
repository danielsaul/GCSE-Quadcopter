/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : receiver.h
  #Author   : Daniel Saul

 */

// Channels:
// 1. Pitch         (Forward/backward)
// 2. Roll          (Left/Right)
// 3. Throttle      (Up/Down)
// 4. Yaw           (Spin Left/Right)
// 5. Motor Arming

int rxmin = 1000;
int rxcentre = 1500;
int rxmax = 2000;
int currentChannel;
int rxraw [5] = { 1500, 1500, 1000, 1500, 1500 };
long rxnow;
long rxprev;
unsigned long rxdiff;
boolean rxready;

void setupReceiver(){

    pinMode(RX_IN,INPUT);                       // Set the pin as input
    attachInterrupt(0,rx_trigger,RISING);       // Interrupt on receiver pin for when it goes from low to HIGH
   
    digitalWrite(STATUS_LED,HIGH);              //Flash Status LED
    delay(50);
    digitalWrite(STATUS_LED,LOW)l

}

void rx_trigger(){

    rxnow = micros();                           // Get the current running time in microseconds
    if(rxprev > 0){                                         
        rxdiff = rxnow - rxprev;                // Work out the length of time since the last 'high' pulse
        if(rxdiff > 5000){                      // If the difference is bigger than 5000uS, then it is now back to the first channel again
            // On boot, it may take a few time before its at the beginning - this lets us know that we know its now at the beginning and we can start.
            rxready = true; 
            currentChannel = 0;
        }else{
            // Check that we are ready to be reading values - if we've only just started then this will be false
            if rxready = true{                             
                if(rxdiff >= 1000 && rxdiff <= 2000){
                    // If the difference is between 1000 and 2000, it is valid and saved as the raw value of that channel.
                    rxraw[currentChannel] = rxdiff; 
                }
                            
                currentChannel++;               // Now onto the next channel
            }
        }
    }
    rxprev = rxnow;

}

void 
