#include <Wire.h> 

int counter = 0;

void setup_i2c_dac() 
{ 
  //Serial.begin(9600);
  //Wire.begin();             
  //delay(1000);
  //Serial.println("setting up DAC");
} 
 
void get_i2c_dac(int DACval) 
{
  const int I2C_address = 76;  // I2C write address 
  
  byte DAT0;                    // I2C data
  byte DAT1;                    // I2C data
  
  //delay(100);
  
  DAT1 = DACval >> 4;            // Ctrl/MS-Byte (2 zeros, PD1&PD0 = 0, 4 data bits) 
  DAT0 = DACval << 4;            // LS-Byte: (4 bits data, 4 bits don't care)
    
  // Setup DAC
  Wire.beginTransmission(I2C_address);
  Wire.send(DAT1);
  Wire.send(DAT0);
  Wire.endTransmission(); 
  Serial.print("DAC Sent Value");
}
