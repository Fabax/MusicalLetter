#define LED1PIN 13
#define SERVO1 7
#define SERVO2 8
#define BUZZ 4

#include <Servo.h>
#include <TimedAction.h>

String inputString = ""; 
boolean stringComplete = false;

Servo monServo1;
Servo monServo2;

//TimedAction servoAction = TimedAction(50, servoAct);

void setup() {
  pinMode(LED1PIN, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  monServo1.attach(SERVO1);
  monServo2.attach(SERVO2);
  monServo1.write(135);
  monServo2.write(135);
  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() {
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

//void servoAct()
//{
//if (Serial.available()) {
void serialEvent() {
   while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      recupSerial(inputString);
      stringComplete = true;
    }
  }
}


void recupSerial(String mess) {
  int sizeArray = int(mess.length()/2)+1;
  String tab[sizeArray];

  analyseString(mess, tab);

  for (int i = 0; i < sizeArray; i++) {
      listenProcessing(false, tab[i]);
  }
  delay(110);
  for (int j = 0; j < sizeArray; j++) {
      listenProcessing(true, tab[j]);
  }
}

void analyseString(String mess, String ptab[]) {
  int chiffreCurr = 0;
  for (int i = 0; i < mess.length(); i++) {
    String currMess = mess.substring(i, i + 1);
    if (currMess != "-") {
      ptab[chiffreCurr] = currMess;
      chiffreCurr ++;
    }
  }
}

void listenProcessing(boolean on, String message) {
  if (message == "1") {
    if (on == true) {
      digitalWrite(LED1PIN, LOW);
    } else {
      digitalWrite(LED1PIN, HIGH);
    }
  }
  if (message == "2") {
    if (on) {
      monServo1.write(135);
    } else {
      monServo1.write(110);
    }
  }
  if (message == "3") {
    if (on) {
      monServo2.write(135);
    } else {
      monServo2.write(110);
    }
  }
}
