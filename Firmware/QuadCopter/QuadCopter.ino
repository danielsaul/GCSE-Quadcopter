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
#include "accel.h"
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
    setupAccel();

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
            float rollAccelPID = processPID((rxRaw[1]-1500) * 0.0015, kinematicsAngle[XAXIS], pidstuff[3]);
            float pitchAccelPID = processPID((rxRaw[0]-1500) * 0.0015, -kinematicsAngle[YAXIS], pidstuff[4]);
            rollAxis = processPID(rollAccelPID, gyroRate[XAXIS]*1.2, pidstuff[5]);
            pitchAxis = processPID(pitchAccelPID, gyroRate[YAXIS]*1.2, pidstuff[6]);
        }else{
            rollAxis = processPID((rxRaw[1]-1500) * 0.005, gyroRate[XAXIS]*0.8, pidstuff[0]);
            pitchAxis = processPID((rxRaw[0]-1500) * 0.005, gyroRate[YAXIS]*0.8, pidstuff[1]);
        }

        motorSpeed[MOTOR_A] = rxRaw[2] - pitchAxis;
        motorSpeed[MOTOR_C] = rxRaw[2] + pitchAxis;
        motorSpeed[MOTOR_B] = rxRaw[2] - rollAxis;
        motorSpeed[MOTOR_D] = rxRaw[2] + rollAxis;

       for(byte motor = 0; motor < 4; motor++){
            motorSpeed[motor] = constrain(motorSpeed[motor], 1100, 2000);
            if(rxRaw[2] < 1100){
                motorSpeed[motor] = 1100;
            }
       }

        checkRXCommands();
        if(!motorsArmed){
            setMotors(MOTOR_OFFSPEED,MOTOR_OFFSPEED,MOTOR_OFFSPEED,MOTOR_OFFSPEED);
        }

        updateMotors();

        prevTime = loopTime;
    }

}
