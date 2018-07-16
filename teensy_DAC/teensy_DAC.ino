#include <Wire.h> 
int counter = 0;

void setup() 
{ 
  Serial.begin(9600);
  Wire.setSDA(18);
  Wire.setSCL(19);
  Wire.begin();             
  delay(1000);
} 
 
void loop() 
{
  const int I2C_address = 76;  // I2C write address 
  
  byte DACval;                  // Store D/A value
  byte DAT0;                    // I2C data
  byte DAT1;                    // I2C data
  
  delay(1500);
  
  DACval = counter;
  DAT1 = DACval >> 4;            // Ctrl/MS-Byte (2 zeros, PD1&PD0 = 0, 4 data bits) 
  DAT0 = DACval << 4;            // LS-Byte: (4 bits data, 4 bits don't care)
    
  // Setup DAC
  Wire.beginTransmission(I2C_address);
  Wire.send(DAT1);
  Wire.send(DAT0);
  Wire.endTransmission(); 
  if (counter == 255){
    counter = 0; 
  }
  else{
    counter ++;
  }
}
