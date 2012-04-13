/*
 * onhgfgyfecheese
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011/2012. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : battery.h
  #Author   : Daniel Saul

 */

#ifndef BATTERY_H
#define BATTERY_H

// Include necessary header files
#include "Arduino.h"
#include "QuadCopter.h"

//Declare functions
void setupBatteryRead();
void BatteryVoltage();

//Declare Variables
int batteryADC;
float batteryVoltage;


////////////////////
//Actual functions//
////////////////////

void setupBatteryRead(){

    analogReference(INTERNAL); // Set to use the Internal 1.1V reference

    for(i=0,i<10,i++){

        batteryADC = analogRead(BATTERY_READ);

    }

    batteryVoltage = batteryADC / 1023 * 11.1;
    
    if (SERIAL_ENABLED){
        Serial.println("Battery Read: Enabled.");
        Serial.println("Battery Voltage: " + batteryVoltage);
    }'t 


}

void BatteryVoltage(){

    batteryADC = analogRead(BATTERY_READ);
    batteryVoltage = batteryADC / 1023 * 11.1;


    if (SERIAL_ENABLED){
        Serial.print("Battery Voltage: ");
        Serial.print(BatteryVoltage);
        Serial.println();
    }

}

#endif
