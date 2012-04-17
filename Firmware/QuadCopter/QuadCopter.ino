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

    // Status LED
    pinMode(STATUS_LED, OUTPUT);
    digitalWrite(STATUS_LED, HIGH);
    delay(500);
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
    setupGyro();
//    setupAccel();

    prevTime = micros();
}

void loop(){
    
    loopTime = micros();
    diffTime = loopTime - prevTime;

    // 100Hz Loop - runs 100 times a second
    if(diffTime >= 10000) {
        diffTimeSecs = diffTime / 1000000.0;
        
        // Read Sensors
        readADC();
        measureGyro();
        measureAccel();

        calculateKinematics(gyroRate[XAXIS],gyroRate[YAXIS],gyroRate[ZAXIS],filteredAccel[XAXIS],filteredAccel[YAXIS],filteredAccel[ZAXIS],0.0,0.0,0.0,diffTimeSecs);

        //Motor Stuff
        if(!GYRO_MODE){
            float rollAccelPID = updatePID((rxRaw[1]-1500) * 0.0015, kinematicsAngle[XAXIS], ATTITUDE PID);
            float pitchAccelPID = updatePID((rxRaw[0]-1500) * 0.0015, -kinematicsAngle[YAXIS], ATTITUDE PID);
            rollAxis = updatePID(rollAccelPID, gyroRate[XAXIS]*1.2, ATTITUDE GYRO PID);
            pitchAxis = updatePID(pitchAccelPID, gyroRate[YAXIS]*1.2, ATTITUDE GYRO PID);
        }else{
            rollAxis = updatePID((rxRaw[1]-1500) * 0.005), gyroRate[XAXIS]*0.8, RATE PID);
            pitchAxis = updatePID((rxRaw[0]-1500) * 0.005), gyroRate[YAXIS]*0.8, RATE PID);
        }

        

        checkRXCommands();
        if(!motorsArmed){
            setMotors(MOTOR_MINSPEED,MOTOR_MINSPEED,MOTOR_MINSPEED,MOTOR_MINSPEED);
        }

        updateMotors();

        prevTime = loopTime;
    }

    // Motors A and C are opposite
//    int throttleA = throttle - pitchy;
//    int throttleC = throttle + pitchy;

    // Motors B and D are opposite
//    int throttleB = throttle - rollx;
//    int throttleD = throttle + rollx;

}
