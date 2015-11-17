MidiController midiController;
PhotoAnalizer analizer; 
int[] r = new int[3];

void setup() {
  size(900, 540);
  midiController = new MidiController();
  analizer = new PhotoAnalizer(0, this);
}

void draw() {
  // midiController.playingMidi(player);
  analizer.render();
}

void keyPressed() {
  if (key == 'c' || key == 'C') {
    analizer.startAnalizise();
  }

//  if (key == 'b' || key == 'B') {
//    float[] blackPixels = analizer.getBlackPixels();
//    midiController.playingMidi();
//  }
}

