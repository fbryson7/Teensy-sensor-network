#include "DHT.h"
#include "teensy_sensors_test.h"

//other DHT setup
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //needs to be global variable

void setup_DHT(){
  //Serial.println("Setting up DHT");
    dht.begin();
}


void read_DHT(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else{
    Serial.println("Meausurements from DHT1:");
    Serial.print("Temperature (C) = ");
    Serial.println(t);
    Serial.print("Humidity = ");
    Serial.println(h);
  }
  
}



