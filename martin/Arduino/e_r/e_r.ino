#define LED1PIN 13
#define SERVO1 7
#define SERVO2 8
#define BUZZ 4
#include <Servo.h>
Servo monServo1;
Servo monServo2;

int message = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED1PIN, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  monServo1.attach(SERVO1);  
  monServo2.attach(SERVO2);
  monServo1.write(135);
  monServo2.write(135);
}

void loop() {
}
void serialEvent() {
  while (Serial.available()) {
     message=Serial.parseInt(); 
     
     Serial.flush();
     listenProcessing(message);
  }
}
void listenProcessing(int message) {
  switch (message) {
    case 1:
      digitalWrite(LED1PIN, HIGH);
      delayMicroseconds(1000);
      digitalWrite(LED1PIN, LOW);
      break;
    case 2:
      monServo1.write(120);
      delay(110);
      monServo1.write(135);
      break;
    case 3:
      monServo2.write(120);
      delay(110);
      monServo2.write(135);
      break;
    case 6:
      digitalWrite(BUZZ, HIGH);
      delayMicroseconds(1000);
      digitalWrite(BUZZ, LOW);
      break;
  }
}
