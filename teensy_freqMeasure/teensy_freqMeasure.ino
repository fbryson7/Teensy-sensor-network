//https://www.pjrc.com/teensy/td_libs_FreqMeasure.html

#include <FreqMeasure.h>
//runs on pin 3, 4 is unusable with analogWrite()

void setup() {
  Serial.begin(9600);
  FreqMeasure.begin();
  tone(5,50);
  Serial.println("Commanded Frequency:    Measured Frequency:");
  Serial.println("___________________     ____________________");
}

double sum=0;
int count=0;

int wavecount = 0;
int freq = 50;

uint32_t t1, t2;

void loop() {
  wavecount++;

  if(wavecount%2000000 == 0 && freq <= 250){
    freq += 25;
    tone(5,freq);
  }else if(freq >250){
    freq = 50;
    wavecount = 0;
    tone(5,freq);
  }
  
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 4) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      //Serial.println(frequency);
      Serial.print("        ");
      Serial.print(freq);
      Serial.print(",                     ");
      Serial.println(frequency);
      sum = 0;
      count = 0;
      //Serial.println(micros()-t1);
      //t1 = micros();
    }
  }
}
