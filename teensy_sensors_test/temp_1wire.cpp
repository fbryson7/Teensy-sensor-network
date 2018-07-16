//http://bildr.org/2011/07/ds18b20-arduino/

#include <OneWire.h> 
#include "teensy_sensors_test.h"


void read_1wire_temp(){
//prints the temperature from one DS18S20 in DEG Celsius
OneWire ds(DS18S20_Pin); // on digital pin 2
bool AllSensorsRead = false;
byte data[12];
byte addr[8];
int sensors_read = 0;
while (!AllSensorsRead){
  
if ( !ds.search(addr)) {
//no more sensors on chain, reset search
//ds.reset_search();
//Serial.println("No more sensors on chain");
AllSensorsRead = true;
return;
}

if ( OneWire::crc8( addr, 7) != addr[7]) {
//Serial.println("CRC is not valid!");
return;
}

if ( addr[0] != 0x10 && addr[0] != 0x28) {
//Serial.print("Device is not recognized");
return;
}

ds.reset();
ds.select(addr);
ds.write(0x44,1); // start conversion, with parasite power on at the end

//delay(750); // Wait for temperature conversion to complete

ds.reset();
ds.select(addr); 
ds.write(0xBE); // Read Scratchpad

for (int i = 0; i < 9; i++) { // we need 9 bytes
data[i] = ds.read();
}

//ds.reset_search();

byte MSB = data[1];
byte LSB = data[0];

float tempRead = (int16_t)((MSB << 8) | LSB); //using two's compliment
float TemperatureSum = tempRead / 16;

if (sensors_read == 0){
  Serial.print("ONEWIRE,");
}

//handle printing temperature so that it can be read by the LCM (4 chars at all times):
if (TemperatureSum > 99 || TemperatureSum < -9.99){
  Serial.print(TemperatureSum,1);
}else if (TemperatureSum > 0 && TemperatureSum < 9.99){
  Serial.print("0");
  Serial.print(TemperatureSum);
}else{
  Serial.print(TemperatureSum);
}
Serial.print(",");
sensors_read ++;

if (sensors_read >= 5){
  AllSensorsRead = true;
}
}
}
