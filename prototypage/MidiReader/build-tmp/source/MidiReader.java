import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import javax.sound.midi.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MidiReader extends PApplet {


public void setup() {
  try {
    File midiFile = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader/data/WIW_NOEL_test_midi.mid"));
    Sequence sequence = MidiSystem.getSequence(midiFile);
    sequencer.setSequence(sequence);
    sequencer.start();
  } catch(Exception e) {}
}


  
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MidiReader" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
