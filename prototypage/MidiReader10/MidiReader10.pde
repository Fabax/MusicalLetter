MidiController midiController;
PhotoAnalizer analizer; 
int[] r = new int[3];
boolean isLetterDetected = false;

void setup() {
  size(900, 540);
  midiController = new MidiController();
  analizer = new PhotoAnalizer(3, this);
}

void draw() {
  analizer.render();
//  if(analizer.isLetterDetected()){
//    isLetterDetected = true;
//    //analizer.render();
//   // println("letter detected: ");
//  }else{
//   // println("letter not detectes: ");
//  }
}

void keyPressed() {
  if (key == 'a' || key == 'A') {
    // midiController.assemblePattern();
    for (int i = 1; i <= 3; ++i) {
      //   midiController.playingMidi(i);
    }
  }
  if (key == 'c' || key == 'C') {
    analizer.runAnalize();
  }

  if (key == 'b' || key == 'B') {
    //midiController.playingMidi();
  }
}

