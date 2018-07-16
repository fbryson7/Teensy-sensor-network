#include <BME280_MOD-1022.h>
#include <Wire.h>

void setup_BME(){
}

void read_BME(){

  BME280.readCompensationParams();

  BME280.writeOversamplingPressure(os1x);  // 1x over sampling (ie, just one sample)
  BME280.writeOversamplingTemperature(os1x);
  BME280.writeOversamplingHumidity(os1x);

  BME280.writeStandbyTime(tsb_0p5ms);        // tsb = 0.5ms
  BME280.writeFilterCoefficient(fc_16);      // IIR Filter coefficient 16
  BME280.writeOversamplingPressure(os16x);    // pressure x16
  BME280.writeOversamplingTemperature(os2x);  // temperature x2
  BME280.writeOversamplingHumidity(os1x);     // humidity x1
  
  BME280.writeMode(smNormal);
  
  BME280.readMeasurements();
  while (BME280.isMeasuring()) {};

  Serial.print("BME,");
  
  //make sure the temperature is always 4 chars:
  float temp = BME280.getTemperature();
  if (temp > 99 || temp < -9.99){
    Serial.print(temp,1);
  }else if(temp > 0 && temp < 9.99){
    Serial.print("0");
    Serial.print(temp);
  }else{
    Serial.print(temp);
  }
  Serial.print(",");

  //make sure the humidity is 4 chars:
  float humid = BME280.getHumidity();
  if (humid<10.00){
    Serial.print("0");
    Serial.print(humid);
  }else if(humid > 99.99){
    Serial.print(humid,1);
  }else{
    Serial.print(humid);
  }
  Serial.print(",");

  //Make sure pressure is 5 chars (expected 3 integer, 2 decimal)
  float pressure = BME280.getPressure();
  if(pressure<100.00){
    Serial.print("0");
    Serial.print(pressure);
  }else if (pressure>999.99){
    Serial.print(pressure,1);
  }else{
    Serial.print(pressure);
  }
  Serial.print(",");
}
