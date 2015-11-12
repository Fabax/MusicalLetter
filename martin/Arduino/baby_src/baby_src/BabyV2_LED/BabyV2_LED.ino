#include <Adafruit_NeoPixel.h>

#define PIN1 12
#define PIN2 10

Adafruit_NeoPixel stripRed = Adafruit_NeoPixel(36, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripBlue = Adafruit_NeoPixel(36, PIN2, NEO_GRB + NEO_KHZ800);

char currentStep = 0;
unsigned long lastAnimWaitingP = 0;

bool isWaiting = false;
bool isMBall = false;
unsigned long cuDelay = 2000;

int message = 0;

String cuCMD = "";
char strValue[6];
int index = 0;
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);
  cuCMD.reserve(200);
  randomSeed(analogRead(0));
  // put your setup code here, to run once:
  stripRed.begin();
  stripRed.show(); // Initialize all pixels to 'off'
  stripRed.setBrightness(100);
  
  stripBlue.begin();
  stripBlue.show(); // Initialize all pixels to 'off'
  stripBlue.setBrightness(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if(stringComplete){
    Serial.println(cuCMD);
    checkInstLed(atoi(cuCMD));
    // clear the string:
    
    cuCMD = "";
    stringComplete = false;
  }*/
  //
  if(isMBall)
  {
    delay(cuDelay);
    if(cuDelay > 100) matchBall(cuDelay-100);
    else matchBall(cuDelay);
  }
    
  if(isWaiting)
  {
    delay(1000);
    waitingPlayers();
  }
}

void serialEvent() 
{
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    if(index < 2 && isDigit(inChar))
    {
      strValue[index++] = inChar;
    }
    else
    {
      strValue[index] = 0;
      message = atoi(strValue);
      Serial.println(message);
      checkInstLed(message);
      index = 0;
    }
  }
}

void checkInstLed(int message)
{  
  
   // message = Serial.read()-'0';  // on soustrait le caractère 0, qui vaut 48 en ASCII
    //Serial.println(message);
    isWaiting = false;
    isMBall = false;
    switch (message) {
    case 1:
      switchON();
      break;
    case 2:
      readyToPlay();
      break;
    case 3:
      isWaiting = true;
      waitingPlayers();
      break;
    case 4:
      badgeA();
      break;
    case 5:
      badgeB();
      break;
    case 6:
      gameStart();
      break;
    case 7:
      goalA();
      break;
    case 8:
      goalB();
      break;
    case 9:
      gamelleA();
      break;
    case 10:
      gamelleB();
      break;
    case 11:
      playing();
      break;
    case 12:
      isMBall = true;
      matchBall(2000);
      break;
    case 13:
      winA();
      break;
    case 14:
      winB();
      break;
    case 15:
      share();
      break;
    }
  
}

void switchON()
{
  waveIN(stripRed.Color(255,0,0));
  waveOUT(stripRed.Color(255,255,255));
  lineIN(stripRed.Color(255,0,0),15);
  lineOUT(stripRed.Color(255,255,255),15);
  lineIN(stripRed.Color(0,0,0),15);
}

void readyToPlay()
{
  //rainbowCycle(1, stripRed, stripBlue);
  //rainbow(1, stripRed, stripBlue);
  //equalizer();
  centralEqualizer(0);
  unCentralEqualizer(17);
  centralEqualizer(0);
  unCentralEqualizer(17);
}

void waitingPlayers()
{
  kit(stripRed.Color(255, 0,0),stripRed.Color(0, 0, 0),15,stripRed,stripBlue);
}

void badgeA()
{
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  delay(100);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  delay(100);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  delay(100);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
}

void badgeB()
{
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(100);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(100);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(100);
  AllumeTout(stripRed.Color(0, 0, 0), stripBlue);
}

void gameStart()
{
  waveOUT(stripRed.Color(255,0,0));
  delay(200);
  waveIN(stripRed.Color(0,0,0));
  waveIN(stripRed.Color(255,122,0));
  delay(200);
  waveIN(stripRed.Color(0,0,0));
  waveOUT(stripRed.Color(0,255,0));
  delay(200);
  waveIN(stripRed.Color(0,0,0));
  waveIN(stripRed.Color(255,255,255));
}

void goalA()
{
  lineIN(stripRed.Color(255, 0, 0),5);
  lineIN(stripRed.Color(0, 0, 0),5);
  
  lineOUT(stripRed.Color(255, 0, 0),5);
  lineOUT(stripRed.Color(0, 0, 0),5);
  
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
  AllumeTout(stripRed.Color(0, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
  AllumeTout(stripRed.Color(0, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
  AllumeTout(stripRed.Color(0, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
  AllumeTout(stripRed.Color(0, 0, 0), stripBlue);
}

void goalB()
{
  lineIN(stripRed.Color(255, 255, 255),5);
  lineIN(stripRed.Color(0, 0, 0),5);
  
  lineOUT(stripRed.Color(255, 255, 255),5);
  lineOUT(stripRed.Color(0, 0, 0),5);
  
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
  AllumeTout(stripRed.Color(0, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
  AllumeTout(stripRed.Color(0, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
  AllumeTout(stripRed.Color(0, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  delay(50);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
  AllumeTout(stripRed.Color(0, 0, 0), stripBlue);
}

void gamelleA()
{
  goalA();
}

void gamelleB()
{
  goalB();
}

void playing()
{
  waveIN(stripRed.Color(255,255,255));
}

void matchBall(unsigned long f)
{
  cuDelay = f;
  
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  AllumeTout(stripRed.Color(255, 255, 255), stripBlue);
  
  delay(f);
  
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripRed.Color(255, 0, 0), stripBlue);
}

void winA()
{
  waveOUT(stripRed.Color(255,0,0));
  waveOUT(stripRed.Color(255,255,255));
  waveOUT(stripRed.Color(255,0,0));
  waveOUT(stripRed.Color(255,255,255));
  waveOUT(stripRed.Color(255,0,0));
  waveOUT(stripRed.Color(255,255,255));
  waveOUT(stripRed.Color(255,0,0));
  waveOUT(stripRed.Color(255,255,255));
  waveOUT(stripRed.Color(255,0,0));
  waveIN(stripRed.Color(0,0,0));
  AllumeTout(stripRed.Color(255, 255, 255), stripRed);
  AllumeTout(stripBlue.Color(255, 255, 255), stripBlue);
}

void winB()
{
  
}

void share()
{
  
}


void centralEqualizer(int e)
{
  uint16_t speede = 15;
  uint16_t s = 0;
  uint16_t nb = 0;
  uint16_t nbmax = 36;
  uint16_t c = 17;
  
  nb = 0;
  c = 17;
  
  while(nb <= nbmax)
  {
    uint16_t startl = c - (nb/2);
    uint16_t endl = c + (nb/2);
    for(uint16_t i=startl; i<=endl; i++) {
      //Serial.println(55+(((float(i)-18)/18)*200));
      int pourc = abs((float(i)-18)/18)*200;
      int p = 55 + pourc;
      
      stripRed.setPixelColor(i, stripRed.Color(p,255-p,0));
      stripBlue.setPixelColor(i, stripRed.Color(p,255-p,0));
    }
    stripRed.show();
    stripBlue.show();
    nb += 2;
    delay(speede);
  }
}

void unCentralEqualizer(int e)
{
  uint16_t speede = 15;
  uint16_t s = 0;
  uint16_t nb = 0;
  uint16_t c = 17;
  
  nb = 36;
  c = 17;
  s = 0;
  uint16_t smax = 18;
  while(s < smax)
  {
    uint16_t startl = c - (nb/2);
    uint16_t endl = c + (nb/2);
    for(uint16_t i=0; i<=s; i++) {

      stripRed.setPixelColor(i, stripRed.Color(0,0,0));
      stripBlue.setPixelColor(i, stripRed.Color(0,0,0));
    }
    
    for(uint16_t i=35-s; i<=35; i++) {

      stripRed.setPixelColor(i, stripRed.Color(0,0,0));
      stripBlue.setPixelColor(i, stripRed.Color(0,0,0));
    }
    stripRed.show();
    stripBlue.show();
    s += 1;
    delay(speede);
  }
}

void equalizer()
{
  uint16_t speede = 15;
  uint16_t s = 0;
  uint16_t nb = 0;
  uint16_t c = 18;
  
  nb = 0;
  c = 0;
  s = 0;
  
  while(nb <= 36)
  {
    uint16_t startl = c;
    uint16_t endl = nb;
    
    for(uint16_t i=startl; i<=endl; i++) {
      int p = 55+((float(i)/36)*200);
      
      stripRed.setPixelColor(i, stripRed.Color(p,255-p,0));
      stripBlue.setPixelColor(i, stripRed.Color(p,255-p,0));
    }
    stripRed.show();
    stripBlue.show();
    nb += 1;
    delay(speede);
  }
}


void waveIN(uint32_t color)
{
  uint16_t speede = 15;
  uint16_t s = 0;
  uint16_t nb = 0;
  uint16_t c = 18;
  
  nb = 36;
  c = 18;
  s = 0;
  while(s < 18)
  {
    uint16_t startl = c - (nb/2);
    uint16_t endl = c + (nb/2);
    for(uint16_t i=0; i<=s; i++) {
      stripRed.setPixelColor(i, color);
      stripBlue.setPixelColor(i, color);
    }
    
    for(uint16_t i=35-s; i<=35; i++) {
      stripRed.setPixelColor(i, color);
      stripBlue.setPixelColor(i, color);
    }
    stripRed.show();
    stripBlue.show();
    s += 1;
    delay(speede);
  }
}

void waveOUT(uint32_t color)
{
  uint16_t speede = 15;
  uint16_t s = 0;
  uint16_t nb = 0;
  uint16_t c = 18;
  
  nb = 0;
  c = 18;
  
  while(nb <= 36)
  {
    uint16_t startl = c - (nb/2);
    uint16_t endl = c + (nb/2);
    for(uint16_t i=startl; i<=endl; i++) {
      stripRed.setPixelColor(i, color);
      stripBlue.setPixelColor(i, color);
    }
    stripRed.show();
    stripBlue.show();
    nb += 2;
    delay(speede);
  }
}

void lineIN(uint32_t color,uint16_t speede)
{
  uint16_t s = 0;
  uint16_t nb = 0;
  uint16_t c = 18;
  
  nb = 0;
  c = 0;
  
  while(nb <= 36)
  {
    uint16_t startl = c;
    uint16_t endl = c + nb;
    for(uint16_t i=startl; i<=endl; i++) {
      stripRed.setPixelColor(i, color);
      stripBlue.setPixelColor(i, color);
    }
    stripRed.show();
    stripBlue.show();
    nb += 1;
    delay(speede);
  }
}

void lineOUT(uint32_t color,uint16_t speede)
{
  uint16_t s = 0;
  uint16_t nb = 0;
  uint16_t c = 18;
  
  nb = 36;
  c = 0;
  
  while(nb > 0)
  {
    uint16_t startl = c+nb;
    uint16_t endl = nb;
    for(uint16_t i=startl; i<=endl; i++) {
      stripRed.setPixelColor(i, color);
      stripBlue.setPixelColor(i, color);
    }
    stripRed.show();
    stripBlue.show();
    nb -= 1;
    delay(speede);
  }
}

void kitinv(uint32_t c,uint32_t c2,uint8_t wait, Adafruit_NeoPixel strip1, Adafruit_NeoPixel strip2)
{
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  
  strip1.show();
  strip2.show();
  
  int k = 0;
  int numL = 10;
  int nbLed = strip1.numPixels();
  for(uint16_t i=k; i<k+10; i++) 
  {
      strip1.setPixelColor(i, c);
      strip1.show();
      delay(wait+20-(k*2));
  }
    
  while(k < nbLed - numL)
  {
    strip1.setPixelColor(k, c2);
    strip1.setPixelColor(k+10, c);
    strip1.show();
    delay(wait);
    k++;
  }
  
  for(uint16_t l=nbLed-10; l<nbLed; l++) 
  {
      strip1.setPixelColor(l, c2);
      strip1.show();
      delay(wait+20-((nbLed-l)*2));
  }
  
  k = nbLed;
  
  for(uint16_t i=nbLed; i>nbLed-10; i--) 
  {
      strip2.setPixelColor(i, c);
      strip2.show();
      delay(wait+20-((nbLed-i)*2));
  }
    
  while(k > numL)
  {
    strip2.setPixelColor(k, c2);
    strip2.setPixelColor(k-10, c);
    strip2.show();
    delay(wait);
    k--;
  }
  
  for(int16_t l=10; l>=0; l--) 
  {
      strip2.setPixelColor(l, c2);
      strip2.show();
      delay(wait+20-(l*2));
  }
}

void kit(uint32_t c,uint32_t c2,uint8_t wait, Adafruit_NeoPixel strip1, Adafruit_NeoPixel strip2)
{
 // AllumeTout(stripRed.Color(0, 0, 0),stripRed);
 // AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  
  int k = 0;
  int numL = 10;
  int nbLed = strip1.numPixels();
  for(uint16_t i=k; i<k+10; i++) 
  {
      strip1.setPixelColor(i, c);
      strip2.setPixelColor(i, c);
      strip1.show();
      strip2.show();
      delay(wait+20-(k*2));
  }
    
  while(k < nbLed - numL)
  {
    strip1.setPixelColor(k, c2);
    strip1.setPixelColor(k+10, c);
    strip2.setPixelColor(k, c2);
    strip2.setPixelColor(k+10, c);
    strip1.show();
    strip2.show();
    delay(wait);
    k++;
  }
  
  for(uint16_t l=nbLed-10; l<nbLed; l++) 
  {
      strip1.setPixelColor(l, c2);
      strip2.setPixelColor(l, c2);
      strip1.show();
      strip2.show();
      delay(wait+20-((nbLed-l)*2));
  }
  
  k = nbLed;
  
  for(uint16_t i=nbLed; i>nbLed-10; i--) 
  {
      strip1.setPixelColor(i, c);
      strip2.setPixelColor(i, c);
      strip1.show();
      strip2.show();
      delay(wait+20-((nbLed-i)*2));
  }
    
  while(k > numL)
  {
    strip1.setPixelColor(k, c2);
    strip1.setPixelColor(k-10, c);
    strip2.setPixelColor(k, c2);
    strip2.setPixelColor(k-10, c);
    strip1.show();
    strip2.show();
    delay(wait);
    k--;
  }
  
  for(int16_t l=10; l>=0; l--) 
  {
      strip1.setPixelColor(l, c2);
      strip2.setPixelColor(l, c2);
      strip1.show();
      strip2.show();
      delay(wait+20-(l*2));
  }
}


/*void waitingPlayers()
{
  colorWipeDouble(stripRed.Color(255, 0, 0),stripRed.Color(0, 0, 0),10,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(255, 0, 0),10,stripRed,stripBlue);
  
  colorWipeDouble(stripRed.Color(0, 0, 255),stripRed.Color(0, 0, 0),10,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(0, 0, 255),10,stripRed,stripBlue);
  
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(0, 0, 0),10,stripRed,stripBlue);
  lastAnimWaitingP = millis();
}*/


void initWifi()
{
  
  //Serial.println("initWifi");
  AllumeTout(stripRed.Color(255, 0, 0), stripRed);
  delay(1000);
  AllumeTout(stripRed.Color(0, 0, 0), stripRed);
  
  AllumeTout(stripBlue.Color(255, 0, 0), stripBlue);
  delay(1000);
  AllumeTout(stripBlue.Color(0, 0, 0), stripBlue);
}

void wifiConnectedLED()
{
  AllumeTout(stripRed.Color(0, 255, 0), stripRed);
  AllumeTout(stripBlue.Color(0, 255, 0), stripBlue);
  
  delay(2000);
  currentStep = 3;
}

void BluePlayerConnect1()
{
  colorWipe1(stripBlue.Color(255, 0, 0), 20, stripBlue); 
}

void BluePlayerConnect2()
{
  colorWipe2(stripBlue.Color(255, 0, 0), 20, stripBlue); 
}

void RedPlayerConnect1()
{
  colorWipe1(stripRed.Color(0, 0, 255), 20, stripRed); 
}

void RedPlayerConnect2()
{
  colorWipe2(stripRed.Color(0, 0, 255), 20, stripRed);
}

void StartGame ()
{
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay(1000);
  stripRed.show();
  stripBlue.show();
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay(1000);
  stripRed.show();
  stripBlue.show();
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay(1000);
  stripRed.show();
  stripBlue.show();
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay(1000);
  stripRed.show();
  stripBlue.show();
  
}

void DefaultGameLED()
{
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  
 // stripRed.setPixelColor(0, stripRed.Color(255, 255, 255));
  //stripBlue.setPixelColor(0, stripBlue.Color(255, 255, 255));
  
 // stripRed.setPixelColor(1, stripRed.Color(255, 255, 255));
 // stripBlue.setPixelColor(1, stripBlue.Color(255, 255, 255));
  
 /* for(uint16_t i=4; i<=6; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
  }
  
  for(uint16_t i=9; i<=11; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
  }
  
  for(uint16_t i=14; i<=16; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
  }*/
  
  /*for(uint16_t i=19; i<=21; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
  }
  
  for(uint16_t i=24; i<=26; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
  }*/
  
  /*for(uint16_t i=29; i<=31; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
  }
  
  for(uint16_t i=34; i<=35; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
  }*/
  uint16_t speede = 15;
  uint16_t s = 0;
  uint16_t nb = 0;
  uint16_t c = 18;
  
  nb = 36;
  c = 18;
  s = 0;
  while(s < 16)
  {
    uint16_t startl = c - (nb/2);
    uint16_t endl = c + (nb/2);
    for(uint16_t i=0; i<=s; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
    }
    
    for(uint16_t i=35-s; i<=35; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
    }
    stripRed.show();
    stripBlue.show();
    s += 1;
    delay(speede);
  }
  
  nb = 0;
  c = 18;
  
  while(nb <= 36)
  {
    uint16_t startl = c - (nb/2);
    uint16_t endl = c + (nb/2);
    for(uint16_t i=startl; i<=endl; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
    }
    stripRed.show();
    stripBlue.show();
    nb += 2;
    delay(speede);
  }
  
  nb = 0;
  c = 18;
  while(nb <= 36)
  {
    uint16_t startl = c - (nb/2);
    uint16_t endl = c + (nb/2);
    for(uint16_t i=startl; i<=endl; i++) {
      stripRed.setPixelColor(i, stripRed.Color(0, 0, 0));
      stripBlue.setPixelColor(i, stripBlue.Color(0, 0, 0));
    }
    stripRed.show();
    stripBlue.show();
    nb += 2;
    delay(speede);
  }
  
  nb = 36;
  c = 18;
  s = 0;
  while(s < 18)
  {
    uint16_t startl = c - (nb/2);
    uint16_t endl = c + (nb/2);
    for(uint16_t i=0; i<=s; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
    }
    
    for(uint16_t i=35-s; i<=35; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
    }
    stripRed.show();
    stripBlue.show();
    s += 1;
    delay(speede);
  }
  
  /* for(uint16_t i=0; i<=35; i++) {
      stripRed.setPixelColor(i, stripRed.Color(255, 255, 255));
      stripBlue.setPixelColor(i, stripBlue.Color(255, 255, 255));
  }*/
  
  
}
  
void GoalBlueTeam ()
{
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (350);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (350);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (350);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (350);
  
  colorWipeDouble(stripRed.Color(0, 0, 255),stripRed.Color(0, 0, 0),10,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(0, 0, 255),10,stripRed,stripBlue);
  
  colorWipeDouble(stripRed.Color(0, 0, 255),stripRed.Color(0, 0, 0),10,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(0, 0, 255),10,stripRed,stripBlue);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (350);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (350);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (350);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (350);
  
  DefaultGameLED();
 }
 
 void GoalRedTeam ()
{
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (500);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (500);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (500);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (500);
  
  colorWipeDouble(stripRed.Color(255, 0, 0),stripRed.Color(0, 0, 0),10,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(255, 0, 0),10,stripRed,stripBlue);
  
  colorWipeDouble(stripRed.Color(255, 0, 0),stripRed.Color(0, 0, 0),10,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(255, 0, 0),10,stripRed,stripBlue);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (500);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (500);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (500);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (500);
  
  DefaultGameLED();
 }

/*void Goal1(uint32_t c, uint8_t wait, Adafruit_NeoPixel strip) {
  for(uint16_t i=59; i>=0; i--) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void Goal2(uint32_t c, uint8_t wait, Adafruit_NeoPixel strip) {
  for(uint16_t i=0; i<=59; i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}*/


void AllumeTout(uint32_t c, Adafruit_NeoPixel strip) {
  for(uint16_t i=0; i<=59; i++) {
      strip.setPixelColor(i, c);   
  }
  strip.show();
}

void AllumeTout2(uint32_t c, Adafruit_NeoPixel strip) {
  for(uint16_t i=30; i<=59; i++) {
      strip.setPixelColor(i, c);   
  }
  strip.show();
}

void RedTeamWin()
{
  colorWipeDouble(stripRed.Color(255, 255, 0),stripRed.Color(0, 0, 0),5,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(255, 255, 0),5,stripRed,stripBlue);
  
  colorWipeDouble(stripRed.Color(255, 255, 0),stripRed.Color(0, 0, 0),5,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(255, 255, 0),5,stripRed,stripBlue);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (300);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (300);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (150);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (150);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (100);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (100);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (50);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (50);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (50);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (50);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (500);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (500);
  
  AllumeTout(stripRed.Color(255, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 0, 0),stripBlue);
  delay (500);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (500);
  
  AllumeTout(stripRed.Color(255, 255, 0),stripRed);
  AllumeTout(stripBlue.Color(255, 255, 0),stripBlue);
}
 
void BlueTeamWin()
{
  colorWipeDouble(stripRed.Color(255, 255, 0),stripRed.Color(0, 0, 0),5,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(255, 255, 0),5,stripRed,stripBlue);
  
  colorWipeDouble(stripRed.Color(255, 255, 0),stripRed.Color(0, 0, 0),5,stripRed,stripBlue);
  colorWipeDouble(stripRed.Color(0, 0, 0),stripRed.Color(255, 255, 0),5,stripRed,stripBlue);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (300);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (300);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (150);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (150);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (100);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (100);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (50);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (50);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (50);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (50);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (500);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (500);
  
  AllumeTout(stripRed.Color(0, 0, 255),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 255),stripBlue);
  delay (500);
  AllumeTout(stripRed.Color(0, 0, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 0, 0),stripBlue);
  delay (500);
  
  AllumeTout(stripRed.Color(0, 255, 0),stripRed);
  AllumeTout(stripBlue.Color(0, 255, 0),stripBlue);
  }
 

void colorWipe1(uint32_t c, uint8_t wait, Adafruit_NeoPixel strip) {
  for(uint16_t i=59; i>=30; i--) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorWipe2(uint32_t c, uint8_t wait, Adafruit_NeoPixel strip) {
  for(uint16_t i=30; i>=0; i--) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorWipe3(uint32_t c, uint8_t wait, Adafruit_NeoPixel strip) {
  for(uint16_t i=0; i<=30; i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorWipe4(uint32_t c, uint8_t wait, Adafruit_NeoPixel strip) {
  for(uint16_t i=30; i<=59; i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void RemovePlayerBlue2()
{
  colorWipe3(stripBlue.Color(0, 0, 0), 20, stripBlue);
}

void RemovePlayerRed2()
{
  colorWipe3(stripRed.Color(0, 0, 0), 20, stripRed);
}

void RemovePlayerBlue1()
{
  colorWipe4(stripBlue.Color(0, 0, 0), 20, stripBlue);
}

void RemovePlayerRed1()
{
  colorWipe4(stripRed.Color(0, 0, 0), 20, stripRed);
}



//________________________________________NEO PIXEL METHOD___________________________________________



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait, Adafruit_NeoPixel strip) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorWipeDouble(uint32_t c,uint32_t c2, uint8_t wait, Adafruit_NeoPixel strip, Adafruit_NeoPixel strip2) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip2.setPixelColor(i, c2);
      strip.show();
      strip2.show();
      delay(wait);
  }
}

void doubleRainbow(uint8_t wait) {
  
  //Serial.println("DoubleRainbow");
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<stripRed.numPixels(); i++) 
    {
      stripRed.setPixelColor(i, Wheel((i+j) & 255, stripRed));
      stripBlue.setPixelColor(i, Wheel((i+j) & 255, stripBlue));
    }
    
    stripBlue.show();
    stripRed.show();
    
    delay(wait);
  }
}

void rainbow(uint8_t wait, Adafruit_NeoPixel strip1, Adafruit_NeoPixel strip2) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel((i+j) & 255, strip1));
      strip2.setPixelColor(i, Wheel((i+j) & 255, strip2));
    }
    strip1.show();
    strip2.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait, Adafruit_NeoPixel strip1, Adafruit_NeoPixel strip2) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255, strip1));
      strip2.setPixelColor(i, Wheel(((i * 256 / strip2.numPixels()) + j) & 255, strip2));
    }
    strip1.show();
    strip2.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, Adafruit_NeoPixel strip) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
