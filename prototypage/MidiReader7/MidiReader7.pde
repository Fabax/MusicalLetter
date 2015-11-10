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
    if(key == 'a' || key == 'A'){
        // midiController.assemblePattern();
        for (int i = 1; i <= 3; ++i) {
        	midiController.playingMidi(i);
        }
    }
    if(key == 'c' || key == 'C'){
	    analizer.startAnalizise();
	}

	if(key == 'b' || key == 'B'){
	    float[] blackPixels = analizer.getBlackPixels();

	    r[0] = (int) random(0, 3);
	    r[1] = (int) random(4, 6);
	    r[2] = (int) random(7, 9);

	     for (int i = 0; i < 3; ++i) {
        	midiController.playingMidi(r[i]);
              }
	}
}
