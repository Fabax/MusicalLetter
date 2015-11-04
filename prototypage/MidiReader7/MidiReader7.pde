MidiController test;
Player player = new Player();

void setup() {
    test = new MidiController();
}

void draw() {
    // test.playingMidi(player);
}

void keyPressed() {
    if(key == 'a' || key == 'A'){
        test.assemblePattern();
        test.playingMidi(player);
    }
}