import serial
import time



sendSerial = serial.Serial("COM3", 9600)
time.sleep(2)
sendSerial.write(123)