import serial
import time

serial_port = "/dev/cu.usbmodem14101"

sendSerial = serial.Serial(serial_port, 9600)

time.sleep(2)

#int headX, int headY, int neckX, int neckY, int rShouX, int rShouY, int rElboX, int rElboY, int rHandX, int rHandY, int pelvX, int pelvY

sendSerial.write(str.encode('15\n5\n15\n9\n12\n12\n8\n12\n5\n14\n20\n30'))