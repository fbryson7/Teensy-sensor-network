#!/usr/bin/python

import serial
import lcm
import time
#from test_msgs import test_msg
from teensy_sensor_data import query_msg

def main():  
  lc = lcm.LCM()

  #Send one query message:
  msg = query_msg()
  msg.timestamp = 0
  msg.query = "query"

  lc.publish("QUERY", msg.encode())

if __name__ == '__main__':
  main()
    
