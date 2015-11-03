import javax.sound.midi.*;

import org.jfugue.midi.MidiParser;
import org.jfugue.pattern.Pattern;
import org.jfugue.player.Player;
import org.staccato.StaccatoParserListener;



MidiParser parser; 
StaccatoParserListener listener;
Player player;


void setup() {
  parser = new MidiParser();
  listener = new StaccatoParserListener();
  player = new Player();

  parser.addParserListener(listener);

  try {
    File midiFile = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader/data/WIW_NOEL_test_midi.mid"));
    parser.parse(MidiSystem.getSequence(midiFile));
    Pattern staccatoPattern = listener.getPattern();
    System.out.println(staccatoPattern);

    player.play(staccatoPattern);
  } catch(Exception e) {}

}

void draw(){


}


