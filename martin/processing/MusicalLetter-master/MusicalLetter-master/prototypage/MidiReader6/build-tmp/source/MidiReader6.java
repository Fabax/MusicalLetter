import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import org.jfugue.player.Player; 
import org.jfugue.temporal.TemporalPLP; 
import org.staccato.StaccatoParser; 
import org.jfugue.devtools.DiagnosticParserListener; 
import org.jfugue.pattern.Pattern; 
import java.io.File; 
import java.io.IOException; 
import javax.sound.midi.InvalidMidiDataException; 
import org.jfugue.midi.MidiFileManager; 
import org.jfugue.midi.MidiParserListener; 
import org.jfugue.parser.ParserListenerAdapter; 
import org.jfugue.theory.Note; 
import org.staccato.maps.SolfegeReplacementMap; 
import org.staccato.ReplacementMapPreprocessor; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MidiReader6 extends PApplet {

















private static final long TEMPORAL_DELAY = 0;
Player player;
File midiFile = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader/data/WIW_NOEL_test_midi.mid"));

public void setup() {
      player = new Player();

    try {
      Pattern pattern = MidiFileManager.loadPatternFromMidi(midiFile);
      // System.out.println(pattern);
    // Part 1. Parse the original music
      StaccatoParser parser = new StaccatoParser();
      TemporalPLP plp = new TemporalPLP();
      parser.addParserListener(plp);
      parser.parse(pattern);

      // Part 2. Send the events from Part 1, and play the original pattern with a delay
      CustomParser dpl = new CustomParser(player); // Or your AnimationParserListener!
      plp.addParserListener(dpl);

      
      // player.delayPlay(TEMPORAL_DELAY, pattern);
      plp.parse();
    } catch(Exception e) {}
}

public void draw(){

}

class CustomParser extends ParserListenerAdapter{

    
    CustomParser(Player player){ 
      println("lol: ");
    }//Fin de la m\u00e9thode main

    @Override
    public void onNoteParsed(Note note) {        
        println("-----------------------------------");
        
        println("note value: "+note.getValue());
        println("note duration: "+note.getDuration());
        println("note getToneString: "+note.getToneString(note.getValue()));
        println("note getToneStringWithoutOctave: "+note.getToneStringWithoutOctave(note.getValue()));
        
    }

    @Override
    public void onTrackChanged(byte track){
      // println("track: "+track);
    }

    @Override
    public void onMarkerParsed(java.lang.String marker){
      // println("marker: "+marker);
    }

    @Override
    public void onNotePressed(Note note){

      // println("note: "+note);
    }
}

// midiFile = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader/data/WIW_NOEL_test_midi.mid"));

  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MidiReader6" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
