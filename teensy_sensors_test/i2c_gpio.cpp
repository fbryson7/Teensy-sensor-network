/******************************************************************************
Example program I2C-16IO interface with Arduino.

SETUP:    I2C-16IO => Arduino
          PIN11 => ground, PIN20 => A5, PIN21 => A4, PIN22 => +5V
Note:     The program is written for address 0x40 (Arduino address 0x20).
          This program was tested using Arduino Nano
Document: PCA9535 datasheet
Updated:  September 4, 2008
E-mail:   support@gravitech.us
          Gravitech
(C) Copyright 2008 All Rights Reserved
*******************************************************************************/

#include <Wire.h> 

/*******************************************************************************
                      Setup
*******************************************************************************/ 
void setup_i2c_gpio() 
{ 
  //Serial.begin(9600);
  //Wire.begin();             // join i2c bus (address optional for master) 
  //delay(1000);
  //Serial.println("setting up gpio");

  const int I2C_address = 0x20;  // I2C write address 
  Wire.beginTransmission(I2C_address);
  Wire.send(3);                // Set output port to %10101010
  Wire.send(0x00);        
  Wire.endTransmission();
  Wire.beginTransmission(I2C_address);
  Wire.send(2);                // Set output port to %10101010
  Wire.send(0x00);        
  Wire.endTransmission(); 

} 
 
/*******************************************************************************
                      Main Loop
*******************************************************************************/  
void get_i2c_gpio() 
{
  const int I2C_address = 0x20;  // I2C write address 
  byte  Data_In;            // Input data
  byte  Data_Out;           // Output data 
  
  Data_Out = 0x0;          // Intialize output data
/*
  Wire.beginTransmission(I2C_address);
  Wire.send(3);                // Set output port to %10101010
  Wire.send(0x00);        
  Wire.endTransmission();
  Wire.beginTransmission(I2C_address);
  Wire.send(2);                // Set output port to %10101010
  Wire.send(0x00);        
  Wire.endTransmission(); 
*/
  Serial.print("GPIO,");
  Wire.beginTransmission(I2C_address);
  Wire.send(0);                // Set the pointer to REGISTER0
  Wire.endTransmission(); 

  
  Wire.requestFrom(I2C_address, 2);
  while(Wire.available())      // Check for data from slave
    { 
      Data_In = Wire.receive();  // receive a byte as character
      if(Data_In < 16){
        Serial.print("0");
      }
      Serial.print(Data_In,HEX);
      Serial.print(",");
    } 
  
  //Display status of PORT0
   
  //}  
}

