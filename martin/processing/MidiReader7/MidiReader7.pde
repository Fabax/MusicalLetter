import processing.serial.*;
MidiController midiController;
//PhotoAnalizer analizer; 
int[] r = new int[3];
PApplet that = this;
String inString;
Serial myPort;

int lf = 6;

void setup() {
  size(900, 540);
  midiController = new MidiController();
  myPort = new Serial(this, "COM22", 9600);
}

void draw() {
    // midiController.playingMidi(player);
     //analizer.render();
     background(0);
     
}

void keyPressed() {
  if (key == 'a' || key == 'A') {
    // midiController.assemblePattern();
    for (int i = 1; i <= 3; ++i) {
      midiController.playingMidi(i);
    }
  }
  if (key == 'c' || key == 'C') {
    //	    analizer.startAnalizise();
  }

  if (key == 'b' || key == 'B') {
    //	    float[] blackPixels = analizer.getBlackPixels();

    r[0] = (int) random(0, 3);
    r[1] = (int) random(4, 6);
    r[2] = (int) random(7, 9);

    //for (int i = 0; i < 3; ++i) {
    midiController.playingMidi(1);
    //}
  }
}