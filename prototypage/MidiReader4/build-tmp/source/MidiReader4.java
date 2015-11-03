import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.io.File; 
import java.io.IOException; 
import javax.sound.midi.InvalidMidiDataException; 
import javax.sound.midi.MidiSystem; 
import org.jfugue.midi.MidiParser; 
import org.jfugue.parser.ParserListenerAdapter; 
import org.jfugue.theory.Note; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MidiReader4 extends PApplet {











File midiFile = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader/data/WIW_NOEL_test_midi.mid"));

public void setup() {
  
    try {
       MidiParser parser = new MidiParser(); // Remember, you can use any Parser!
        MyParserListener listener = new MyParserListener();
        parser.addParserListener(listener);
        parser.parse(MidiSystem.getSequence(midiFile));
        System.out.println("There are " + listener.counter + " 'C' notes in this music.");
    } catch(Exception e) {}

   

}

class MyParserListener extends ParserListenerAdapter {
    public int counter;

    @Override
    public void onNoteParsed(Note note) {
      
        // A "C" note is in the 0th position of an octave
        if (note.getPositionInOctave() == 0) {
            counter++;
        }
    }
}


  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MidiReader4" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
