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
void setup() 
{ 
  Serial.begin(9600);
  Wire.begin();             // join i2c bus (address optional for master) 
  delay(1000);
} 
 
/*******************************************************************************
                      Main Loop
*******************************************************************************/  
void loop() 
{
  const int I2C_address = 0x20;  // I2C write address 
  byte  Data_In;            // Input data
  byte  Data_Out;           // Output data 
  
  Data_Out = 0x55;          // Intialize output data
  
  Wire.beginTransmission(I2C_address);
  Wire.send(6);             // Configure PORT 0 and PORT 1
  Wire.send(0xFF);          // P0.7 6 5 4 3 2 1 0
  Wire.send(0x00);          //   I  I I I I I I I 
  Wire.endTransmission();   // P1.7 6 5 4 3 2 1 0
                            //   O  O O O O O O O
                            
  Wire.beginTransmission(I2C_address);
  Wire.send(3);             // Set output port to %01010101
  Wire.send(Data_Out);        
  Wire.endTransmission(); 
 
  while(1)
  {
    delay (1000);
    Data_Out = Data_Out ^ 0xFF; // Invert all of the bits
    Wire.beginTransmission(I2C_address);
    Wire.send(3);                // Set output port to %10101010
    Wire.send(Data_Out);        
    Wire.endTransmission(); 
    
    Wire.beginTransmission(I2C_address);
    Wire.send(0);                // Set the pointer to REGISTER0
    Wire.endTransmission(); 
    
    Wire.requestFrom(I2C_address, 2);
    
    while(Wire.available())      // Checkf for data from slave
    { 
      Data_In = Wire.receive();  // receive a byte as character 
      Serial.println(Data_In, HEX);
    } 
    
    //Display status of PORT0
    Serial.print("PORT0 = ");
     
  }  
}

