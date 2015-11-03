import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.io.BufferedInputStream; 
import java.io.File; 
import java.io.FileInputStream; 
import java.io.InputStream; 
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







long tick; 
float tempoFactor ;
Sequencer sequencer ;

public void setup() {
  try {
    // File midiFile = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader/data/WIW_NOEL_test_midi.mid"));
    sequencer = MidiSystem.getSequencer();
    sequencer.open();
    InputStream is = new BufferedInputStream(new FileInputStream(new File("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader/data/WIW_NOEL_test_midi.mid")));
	sequencer.setSequence(is);

	sequencer.addMetaEventListener(new MetaEventListener() {
	    public void meta(MetaMessage event) {
	        if (event.getType() == 88) {
	            System.out.println("Sequencer started playing");
	        }
	        else if (event.getType() == 47) {
	            System.out.println("Sequencer finished playing");
	        }
	    }
	});

	// Starts playback of the MIDI data in the currently loaded sequence.
	sequencer.start();

  } catch(Exception e) {}
}

public void draw(){
	tick = sequencer.getTickPosition();
	tempoFactor = sequencer.getTempoFactor();
	println("tempoFactor: "+tempoFactor);

}

public void parse(Sequence sequence){
  int tempo=1;
  Track[] tracks=sequence.getTracks();
  long totalCount=0;
  long counter=0;
  for (byte i=0; i < tracks.length; i++) {
    totalCount+=tracks[i].size();
  }
  for (int t=0; t < tracks.length; t++) {
    int trackSize=tracks[t].size();
    if (trackSize > 0) {
      fireVoiceEvent(new Voice((byte)t));
      for (int ev=0; ev < trackSize; ev++) {
        counter++;
        fireProgressReported("Parsing MIDI...",counter,totalCount);
        MidiEvent event=tracks[t].get(ev);
        MidiMessage message=event.getMessage();
        trace("Message received: ",message);
        parse(message,event.getTick());
      }
    }
  }
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
