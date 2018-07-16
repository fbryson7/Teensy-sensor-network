#include <Wire.h>

void setup_i2c_adc() {
}

float get_i2c_adc(int pin) {
  const byte DAT[8] = {0x8C,0xCC,0x9C,0xDC,0xAC,0xEC,0xBC,0xFC}; //defines addresses for channels
  
  byte Low_val;
  byte High_val;
  const byte address = 0x48; //address of the gravitech I2C ADC without R/W digit
  Wire.beginTransmission(address);
  Wire.send(DAT[pin]); //CH2
  Wire.endTransmission();

  //read A/D value
  Wire.requestFrom(address,2);
  while(Wire.available()){
    High_val = Wire.receive();
    Low_val = Wire.receive();
    //int bin = High_val * 256 + Low_val;
    int bin = word(High_val,Low_val);
    float voltage = 0.0006105006 * bin;

    Serial.print(voltage);
    Serial.print(",");
    return voltage;
  }
  
  //delay(1000);
  
}
