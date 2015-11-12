import serial
from mido import MidiFile

port = serial.Serial('com22', 9600)
mid = MidiFile('data.mid')

for message in MidiFile('data.mid').play():
     if message.type == 'note_on':
          print(message)
          if message.note == 72:
               port.write('1\n')
          if message.note == 76:
               port.write('1\n')
          if message.note == 77:
               port.write('1\n')
          if message.note == 79:
               port.write('2\n')
          if message.note == 83:
               port.write('2\n')
          if message.note == 84:
               port.write('2\n')
          if message.note == 86:
               port.write('3\n')
          if message.note == 89:
               port.write('3\n')
          if message.note == 91:
               port.write('3\n')
               
          #port.write('6\n')
          
