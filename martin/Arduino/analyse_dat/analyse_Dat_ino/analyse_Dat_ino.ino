void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
void serialEvent() {
  while (Serial.available()) {
    String message = Serial.readString();
    String tab[message.length()];
    analyseString(message, tab);
    for (int i = 0; message.length(); i++) {
      if(tab[i] != NULL){ 
        Serial.print("res6p:"+tab[i]);
      }
    }
  }
}

void analyseString(String mess, String ptab[]) {
  String currMess = mess;
  int chiffreCurr = 0;

  for (int i = 0; i < mess.length(); i++) {
    currMess = charact(mess);
    if (currMess == "/") {

    }
    else if(currMess == "2" || currMess == "3"){
      ptab[chiffreCurr] = currMess;
      chiffreCurr ++;
    }
  }
}

String charact(String mess) {
  return mess.substring(0, 1);
}


