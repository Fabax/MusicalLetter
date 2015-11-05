MidiController midiController;
PhotoAnalizer analizer; 

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
	    float blackPixels = analizer.getBlackPixels();
	    println("blackPixels: "+blackPixels);
	}


	
}
