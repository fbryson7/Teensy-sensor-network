//Definitions:
//PINS:
#define DHTPIN 2
#define LEAKPIN 1
//#define ONE_WIRE_BUS 4
#define DS18S20_Pin 5

//declare (global) variables

//declare functions:
extern void setup_DHT(); //in DHT.cpp
extern void read_DHT(); //in DHT.cpp

extern void setup_BME(); //in BME280.cpp
extern void read_BME();

extern void setup_i2c_adc(); //in i2c_adc.cpp
float get_i2c_adc(int pin);

extern void get_i2c_dac(int DACval); //in i2c_dac.cpp
extern void setup_i2c_dac() ;

extern void setup_1wire_temp(void); //in teensy_1wire.cpp
extern void read_1wire_temp();

extern void get_i2c_gpio(); //in i2c_gpio.cpp
extern void setup_i2c_gpio() ;

