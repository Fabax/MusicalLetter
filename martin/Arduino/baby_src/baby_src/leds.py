#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial  # bibliothèque permettant la communication série
import time    # pour le délai d'attente entre les messages
import RPi.GPIO as GPIO
import os
import sys

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

ser = serial.Serial('/dev/ttyACM1', 9600, timeout =1)
time.sleep(4)
ser.write('1\n')

while 1 :
	
	inputText = sys.stdin.readline()
	
	if inputText == '1\n' :
		ser.write('1\n')
	
	if inputText == '2\n' :
		ser.write('2\n')

	if inputText == '3\n' :
		ser.write('3\n')
	
	if inputText == '4\n' :
		ser.write('4\n')

	if inputText == '5\n' :
		ser.write('5\n')
	
	if inputText == '6\n' :
		ser.write('6\n')

	if inputText == '7\n' :
		ser.write('7\n')
	
	if inputText == '8\n' :
		ser.write('8\n')

	if inputText == '9\n' :
		ser.write('9\n')
	
	if inputText == '10\n' :
		ser.write('10\n')

	if inputText == '11\n' :
		ser.write('11\n')
	
	if inputText == '12\n' :
		ser.write('12\n')

	if inputText == '13\n' :
		ser.write('13\n')
	
	if inputText == '14\n' :
		ser.write('14\n')

	if inputText == '15\n' :
		ser.write('15\n')
