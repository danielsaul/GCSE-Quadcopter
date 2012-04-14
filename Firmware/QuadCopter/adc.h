/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011/2012. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : adc.h
  #Author   : Daniel Saul

 */

#ifndef ADC_H
#define ADC_H

// Include necessary header files
#include "Arduino.h"
#include "Wire.h"

//Declare functions
void readADC();
long getRawADC(int chnl);
void setupADC();

//Declare variables
volatile uint16_t adcValue[6] = { 0,0,0,0,0,0 };

////////////////////
//Actual functions//
////////////////////

void setupADC(){

    Wire.begin();
    readADC();

    if (SERIAL_ENABLED){
        Serial.println("ADC: Enabled");
    }

}

void readADC(){
  
    for (int i = 0; i < 6; i++){

        //Talk to ADC over I2C bus
        Wire.beginTransmission(0b0110011);
        Wire.write(0b01100001 | ((i & 0b00001111) << 1));
        Wire.endTransmission(); 
        
        //Request all available data from the ADC
        Wire.requestFrom(0b0110011, 2);    
        while(Wire.available())   
        { 
          //14 bit ADC, and each byte only takes 8 bits, hence two bytes needed
          byte a = Wire.read(); 
          byte b = Wire.read();
          uint16_t result = 0x0FFF & ((a << 8) | b);
          adcValue[i] = result;
        }
    }  

}

long getRawADC(int chnl){

    return adcValue[chnl]; 

}

#endif
