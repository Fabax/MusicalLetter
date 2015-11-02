import javax.sound.midi.*;
void setup() {
  try {
    File midiFile = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader/data/WIW_NOEL_test_midi.mid"));
    Sequencer sequencer = MidiSystem.getSequencer();
    sequencer.open();
    Sequence sequence = MidiSystem.getSequence(midiFile);
    sequencer.setSequence(sequence);
    sequencer.start();
  } catch(Exception e) {}
}
