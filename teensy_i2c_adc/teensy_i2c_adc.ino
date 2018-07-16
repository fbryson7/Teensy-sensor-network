#include <Wire.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  
  Wire.setSDA(18);
  Wire.setSCL(19);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte Low_val;
  byte High_val;
  const byte address = 0x48; //address of the gravitech I2C ADC without R/W digit
  Wire.beginTransmission(address);
  Wire.send(0xCC);
  Wire.endTransmission();

  //read A/D value
  Wire.requestFrom(address,2);
  while(Wire.available()){
    High_val = Wire.receive();
    Low_val = Wire.receive();
    //int bin = High_val * 256 + Low_val;
    int bin = word(High_val,Low_val);
    float voltage = 0.0006103515 * bin;

    Serial.println(voltage);

  }

  delay(1000);
  
}
