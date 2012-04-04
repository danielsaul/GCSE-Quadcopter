/*
  QuadCopter - GCSE Electronic Products
  Daniel Saul - www.DanSaul.co.uk
  (C) Copyright 2011. All Rights Reserved.
 
  Arduino-based Quadcopter Control System
 
  #File     : QuadCopter.pde
  #Author   : Daniel Saul

 */

// Include various header files
#include "QuadCopter.h"
//#include "adc.h"
//#include "pid.h"
//#include "receiver.h"
#include <Servo.h>
#include "motors.h"
//#include "accel.h"

/////////////////////////////////
// Main Program Initialisation //
// //////////////////////////////
void setup(){

    // Status LED
    pinMode(STATUS_LED, OUTPUT);
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);

    // Begin Serial to Computer, if enabled
    if (SERIAL_ENABLED) {
        Serial.begin(BAUD_RATE);
        Serial.println("Quadcopter - GCSE Electronic Products");
        Serial.println("Daniel Saul - 2012 \n");
    }
    
//    setupReceiver();    
//    setupADC();
    setupMotors();
//    calibrateAccel();
}

void loop(){
/*
    readADC();
    measureAccel();
    Serial.print(acceleration[0]);
    Serial.print(", ");
    Serial.print(acceleration[1]);
    Serial.print(", ");
    Serial.print(acceleration[2]);
    Serial.print("\n");
    delay(100);
*/

    motorSpeed[0] = 1200;
    motorSpeed[1] = 1200;
    motorSpeed[2] = 1200;
    motorSpeed[3] = 1200;
    updateMotors();
    delay(5000);
    motorSpeed[0] = 1000;
    motorSpeed[1] = 1000;
    motorSpeed[2] = 1000;
    motorSpeed[3] = 1000;
    updateMotors();
    delay(5000);
    

}
