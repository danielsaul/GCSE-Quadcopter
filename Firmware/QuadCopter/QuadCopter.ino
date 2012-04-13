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
#include "adc.h"
#include "pid.h"
#include "receiver.h"
#include "motors.h"
//#include "accel.h"
#include "gyro.h"

/////////////////////////////////
// Main Program Initialisation //
// //////////////////////////////
void setup(){

    // Set outputs
    pinMode(MOTORA_PIN, OUTPUT);
    digitalWrite(MOTORA_PIN, LOW);
    pinMode(MOTORB_PIN, OUTPUT);
    digitalWrite(MOTORB_PIN, LOW);
    pinMode(MOTORC_PIN, OUTPUT);
    digitalWrite(MOTORC_PIN, LOW);
    pinMode(MOTORD_PIN, OUTPUT);
    digitalWrite(MOTORD_PIN, LOW);

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
    
    setupReceiver();    
    setupADC();
    setupMotors();
//    calibrateAccel();
    calibrateGyro();

}

void loop(){
/*
    readADC();
    measureGyro();
    Serial.print(gyroRate[0]);
    Serial.print(", ");
    Serial.print(gyroRate[1]);
    Serial.print(", ");
    Serial.print(gyroRate[2]);
    Serial.print("\n");
    delay(100);
*/
/*
    Serial.print(rx_raw[0]);
    Serial.print(", ");
    Serial.print(rx_raw[1]);
    Serial.print(", ");
    Serial.print(rx_raw[2]);
    Serial.print(", ");
    Serial.print(rx_raw[3]);
    Serial.print(", ");
    Serial.print(rx_raw[4]);
    Serial.print("\n");
    */
    
    long loopTime = micros();

    int throttle = ((rx_raw[2]-1000)/1)+1000; // Scaled to 1/3
        
    readADC();
    measureGyro();

    int rollx = processPID(1500, gyroRate[XAXIS] + 1500, &pidstuff[1]);
    int pitchy = processPID(1500, gyroRate[YAXIS] + 1500, &pidstuff[0]);

    // Motors A and C are opposite
    int throttleA = throttle - pitchy;
    int throttleC = throttle + pitchy;

    // Motors B and D are opposite
    int throttleB = throttle - rollx;
    int throttleD = throttle + rollx;

    throttleA = constrain(throttleA, 1100, 2000);
    throttleB = constrain(throttleB, 1100, 2000);
    throttleC = constrain(throttleC, 1100, 2000);
    throttleD = constrain(throttleD, 1100, 2000);

    setMotors(throttleA,throttleB,throttleC,throttleD);
    
    checkMotorArming();
    if(!motorsArmed){
        setMotors(1000,1000,1000,1000);
        digitalWrite(STATUS_LED, LOW);
    }else{
        digitalWrite(STATUS_LED, HIGH);
    }

    updateMotors();
    
    delay(100);
}
