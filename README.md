# Teensy sensor network

## Code to just run individual sensors (prints results to serial):
teensy_BME280 - for environment sensor, will print the temperature, pressure, and percent relative humidity. Requires the BME280 library in libraries directory

teensy_DAC - for the I2C DAC, manual and code examples can be found from http://www.gravitech.us/i2c8dico.html

teensy_I2CGPIO_test - for the I2C GPIO expander, reports two hex values representing the two ports on the GPIO board (http://www.gravitech.us/i2c16gpex.html)

teensy_freqMeasure - uses the Teensy freqMeasure function to measure the frequency on pin 3. This code is used as a test, and so frequencies are generated on pin 5 (a jumper cable expected from pin 5 to pin 3), and the frequencies are read. The serial port shows a comparison of the expected and measured frequencies.

teensy_i2c_adc - for the I2C ADC, reads a single channel from the ADC (http://www.gravitech.us/i2c128anco.html)

teensy_onewire_temp - for the OneWire temperature sensors: up to 10 sensors can be on one bus, the program will automatically search for the next sensor on the bus and print its temperature to the serial.

libraries: includes libraries for the DHT sensor (not used in this network), and the BME280 environment sensor.

## For LCM integration:
teensy_sensors_test - includes all the code to be run on the Teensy (teensy_sensors_test.ino) when connecting to LCM. Prints the results from the environment sensor, onewire temperature sensor bus, and ADC (check teensy_sensors_test.h for the corresponding pins, I2C runs on SDA=18, SCL=19) to the a serial window. (Additional information (including GPIO, frequency measure, DHT reading, etc.) can be printed, but will require editing the parsing system in teensy_lcm_publisher.py)

teensy_lcm_publisher.py - reads from the serial port, converts the strings into an LCM message, and publishes the message to the channel "TEENSY_DATA". Additionally, checks the channel "QUERY", to determine how much information to ask from the teensy. If a query has been made (by lcm_serial_query), "?" is printed to the serial port to be read by the teensy, and additional information is read and given (ADC data).

teensy_lcm_listener.py - listens to the channel "TEENSY_DATA", and reads and prints the message of data from the sensor network.

lcm_serial_query.py - sends a teensy_query message to the channel "QUERY" to request more information from the teensy (in this case, requesting ADC reading in addition to the BME and OneWire sensor data).
