#!/usr/bin/python

import serial
import lcm
import time
from teensy_sensor_data import teensy_data, query_msg


def main():
  global query
  query = 0

  lc = lcm.LCM()

  subscription = lc.subscribe("QUERY", query_handler)
  
  ser.isOpen()
  while 1:
    try:
      error = 0
      #see how much information should be sent:
      lc.handle_timeout(50)

      #extract the information delimited by commas:
      if query:
        data_str = ser.read(114).split(",")
      else:
        data_str = ser.read(70).split(",")
      data_str[-1] = data_str[-1].strip("\n")
      data_str[-1] = data_str[-1].strip("\r")
      print(data_str)

      #set up the lcm publisher:
      msg = teensy_data()
  
      #assert that the first string is BME:
      if (data_str[0] != "BME"):
        error = 1
      else:
        msg.BME_temp = float(data_str[1])
        msg.BME_pressure = float(data_str[3])
        msg.BME_humidity = float(data_str[2])

      #Assert that the next string is from the leak sensor
      if (data_str[4] == "LEAK"):
        msg.Leak = int(data_str[5])
      else:
        error = 1

      #Assert that the next string is from the onewire sensors:
      if (data_str[6] == "ONEWIRE"):
        msg.OneWireTemp[0] = float(data_str[7])
        msg.OneWireTemp[1] = float(data_str[8])
        msg.OneWireTemp[2] = float(data_str[9])
        msg.OneWireTemp[3] = float(data_str[10])
        msg.OneWireTemp[4] = float(data_str[11])
      else:
        error = 1
      
      #If an ask for more information has been made, check ADC
      if query:
        #Assert that the next string is from the ADC:
        if (data_str[12] == "ADC"):
          for i in range(0,8):
            index = i + 13
            msg.Analog[i] = float(data_str[index])
        else:
          error = 1
        query = 0
  
      if error:
        msg.Error = True
        print("Error: Data not in expected format.")
        #reconnect to serial to get the right format again
        reconnect(ser)
      else:
        msg.Error = False
      lc.publish("TEENSY_DATA", msg.encode())
    except Exception as e:
      reconnect(ser)
      print(e)

def reconnect(handle):
  connected = False
  if not handle:
    print "Could not find serial port"
    quit()
  while not connected:
    try:
      time.sleep(.1)
      handle = serial.Serial('/dev/tty.usbmodem1550531',9600)
      connected = True
    except Exception as e:
      print e

def query_handler(channel, data):
  #write to serial "?" to ask for ADC data
  global query
  query = 1
  ser.write("?")
  
if __name__ == '__main__':
  #configure the serial connections:
  ser = serial.Serial(
    port = '/dev/tty.usbmodem1550531',
    baudrate = 9600,
    parity = serial.PARITY_ODD,
    stopbits = serial.STOPBITS_TWO,
    bytesize = serial.SEVENBITS,
  )
  main()

