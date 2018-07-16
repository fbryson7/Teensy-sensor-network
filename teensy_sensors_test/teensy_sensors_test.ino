#include "teensy_sensors_test.h"
#include <Wire.h>
#include <DallasTemperature.h>
#include <FreqMeasure.h>
//runs on pin 3, 4 is unusable with analogWrite()

double sum=0;
int count=0;
int leak = 0;


void Leak_ISR(){
  leak = 1;
  noInterrupts(); //so the interrupts don't continuously run
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.setSDA(18);
  Wire.setSCL(19);
  Wire.begin();

  //leak sensor
  attachInterrupt(digitalPinToInterrupt(LEAKPIN), Leak_ISR, HIGH);

/*
  //frequency measurements:
  FreqMeasure.begin();
  tone(5,50);
*/
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(250);

 

  //read the BME280
  //read_BME(); //prints the results to screen

/*
  //read the gpio i2c pins
  get_i2c_gpio();
*/
  //Leak sensor:
  Serial.print("LEAK,");
  Serial.print(leak);
  Serial.print(",");

  //temp reading from onewire sensor(s?)
  read_1wire_temp();

  byte x = '0';
  if (Serial.available() > 0) {
    x = Serial.read();
  
    if(x=='?'){
  //get i2c adc values from one channel - can add other iterations:
      Serial.print("ADC,");
      for (int ADC_CH = 0; ADC_CH<8; ADC_CH++){
        get_i2c_adc(ADC_CH);
      }
    }
  }
  Serial.print("\r\n");//start new line

  
  //Extra things that can be added in later - beware of print statements, though!
/*
  //ADC voltage readings from teensy pins:
  float val = 0.003225806 * analogRead(14);
  Serial.print("Analog Voltage Reading: ");
  Serial.println(val);
  Serial.println();
*/

/*
  //frequency measurement (runs continuously)
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 4) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      Serial.print("Frequency Measure: ");
      Serial.println(frequency);
      sum = 0;
      count = 0;
      //Serial.println(micros()-t1);
      //t1 = micros();
    }
  }
*/
}

