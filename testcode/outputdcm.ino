// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(57600);  // start serial for output
  
}

uint16_t values[6];
float voltages[6];
float accvshifts[3];
int accgs[3];
uint16_t result;
void loop()
{
  for (int i = 0; i < 6; i++){
    Wire.beginTransmission(0b0110011);
    Wire.write(0b01100001 | ((i & 0b00001111) << 1));
    //Wire.write(0b01100001);
    Wire.endTransmission();  
    Wire.requestFrom(0b0110011, 2);    
    while(Wire.available())   
    { 
      byte a = Wire.read(); 
      //Serial.println(a);
      byte b = Wire.read();
      //Serial.println(b);
      result = 0x0FFF & ((a << 8) | b);
      values[i] = result;
      //Serial.print(result);
      //if (i < 5){
      //  Serial.print(",");
      //}else{
      //  Serial.print("\n");
      //  delay(1000);
      //}
    }
    voltages[i] = values[i] * 3.3 / 4095;
    if(i<3){
      accvshifts[i] = voltages[i] - 1.5;
      accgs[i] = accvshifts[i] / 0.3;
    }
  }

  //Serial.print("x:");
  //Serial.println(accgs[0]);
  //Serial.print("y:");
  //Serial.println(accgs[1]);
  //Serial.print("z:");
  //Serial.println(accgs[2]);
  //Serial.println();
  //delay(500);
  
  int comPkt[5];
  comPkt[0] = 0xCDAB;                     //Packet Header, indicating start of packet.
  comPkt[1] = 6;                          //Size of data payload in bytes.
  comPkt[2] = accgs[0];    //Channel 1 data. 16bit signed integer
  comPkt[3] = accgs[1];    //Channel 2 data. 16bit signed integer
  comPkt[4] = accgs[2];    //Channel 3 data. 16bit signed integer

  Serial.write((uint8_t *)comPkt,2 + 2 + (3*sizeof(int)));
}
