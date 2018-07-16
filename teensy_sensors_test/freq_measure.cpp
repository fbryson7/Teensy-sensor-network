//https://www.pjrc.com/teensy/td_libs_FreqMeasure.html

#include <FreqMeasure.h>
//runs on pin 3, 4 is unusable with analogWrite()

void setup_freq() {
  Serial.begin(9600);
  FreqMeasure.begin();
  tone(5,50);
  Serial.println("Commanded Frequency:    Measured Frequency:");
  Serial.println("___________________     ____________________");
}

double sumf=0;
int countf=0;

int wavecount = 0;
int freq = 50;

uint32_t t1, t2;

void main_freq() {
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
    sumf = sumf + FreqMeasure.read();
    countf = countf + 1;
    if (countf > 4) {
      float frequency = FreqMeasure.countToFrequency(sumf / countf);
      //Serial.println(frequency);
      Serial.print("        ");
      Serial.print(freq);
      Serial.print(",                     ");
      Serial.println(frequency);
      sumf = 0;
      countf = 0;
      //Serial.println(micros()-t1);
      //t1 = micros();
    }
  }
}
