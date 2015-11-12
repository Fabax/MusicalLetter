import serial
import time
import random

ser = serial.Serial('COM22', 9600, timeout =1)

while 1:
    nextNote = random.randint(1, 5);
    time.sleep(0.1)
    ser.write(''+`nextNote`+'\n')
