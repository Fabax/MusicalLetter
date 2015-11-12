import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import javax.sound.midi.*; 
import org.jfugue.midi.MidiParser; 
import org.jfugue.pattern.Pattern; 
import org.jfugue.player.Player; 
import org.staccato.StaccatoParserListener; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MidiReader2 extends PApplet {








MidiParser parser; 
StaccatoParserListener listener;
Player player;


public void setup() {
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

public void draw(){


}


  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MidiReader2" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
