#!/usr/bin/python

import serial
import lcm
import time
from teensy_sensor_data import teensy_data


def teensy_data_handler(channel, data):
  msg = teensy_data.decode(data)
  print("Received message on channel \"%s\"" % channel)
  print("   Temperature [C]         = %.2f" % msg.BME_temp)
  print("   Humidity [RH]           = %.2f" % msg.BME_humidity)
  print("   Pressure [hPa]          = %.2f" % msg.BME_pressure)
  
#  print("   GPIO Port 0         = %s" % str(msg.GPIO[0]))
#  print("   GPIO Port 1         = %s" % str(msg.GPIO[1]))

  print("   Leak Sensor             = %s" % str(bool(msg.Leak)))

  print("   OneWire Temperature [C] = %0.2f, %0.2f, %0.2f, %0.2f, %0.2f" % msg.OneWireTemp)

  print("   ADC Results [V]         = %0.2f, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f" % msg.Analog)
  print("   Error Reading Data      = %s" %str(msg.Error))

lc = lcm.LCM()
subscription = lc.subscribe("TEENSY_DATA", teensy_data_handler)

try:
  while True:
    lc.handle()
except KeyboardInterrupt:
  pass

lc.unsubscribe(subscription)
  
    

