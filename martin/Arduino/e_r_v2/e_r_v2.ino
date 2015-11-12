#define LED1PIN 13
#define SERVO1 7
#define SERVO2 8

boolean ledState = false;

#include <Servo.h>
#include <TimedAction.h>

Servo monServo1;
Servo monServo2;

//this initializes a TimedAction object that will change the state of an LED every second.
//TimedAction blinkAction                 =       TimedAction(1000,blink);
//this initializes a TimedAction object that will change the state of an LED
//according to the serial buffer contents, every 50 milliseconds
//TimedAction servo1Action = TimedAction(50, servo1Act);
TimedAction servo2Action = TimedAction(50, servo2Act);
//this initializes a TimedAction object that will write tha ascii table to the serial every ten seconds
//TimedAction asciiTableAction    =       TimedAction(10000,asciiTable);


void setup() {
  pinMode(LED1PIN, OUTPUT);
  monServo1.attach(SERVO1);
  monServo2.attach(SERVO2);
  monServo1.write(135);
  monServo2.write(135);
  Serial.begin(9600);
}

void loop() {
  //servo1Action.check(); //trigger every 50 millisecond
  servo2Action.check();
}

//[url=http://arduino.cc/en/Tutorial/PhysicalPixel]Examples->Digital->PhysicalPixel[/url]
/*void servo1Act()
{
  if (Serial.available()) {
    //int message = Serial.parseInt();
    byte val = Serial.read();
    if (val == '3') {
      monServo2.write(120);
      delay(110);
      monServo2.write(135);
    }
  }
}*/


void servo2Act()
{
  if (Serial.available()) {
    //int message = Serial.parseInt();
    byte val = Serial.read();
    //Servo
    if (val == '2') {
      monServo1.write(120);
      monServo2.write(120);
      delay(110);
      monServo1.write(135);
      monServo2.write(135);
    }
  }
}



