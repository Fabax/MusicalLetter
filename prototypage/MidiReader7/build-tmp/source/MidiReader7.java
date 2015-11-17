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
import processing.video.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MidiReader7 extends PApplet {

MidiController midiController;
PhotoAnalizer analizer; 
int[] r = new int[3];

public void setup() {
	size(900, 540);
    midiController = new MidiController();
    analizer = new PhotoAnalizer(0, this);
}

public void draw() {
    // midiController.playingMidi(player);
     analizer.render();
}

public void keyPressed() {
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
















// import org.apache.commons.io.FilenameUtils;

public class MidiController {

  private static final long   TEMPORAL_DELAY = 0;
  File dir;
  String[] list;
  // Pattern[] patterns;
  Pattern finalPattern;
  boolean isMidi;

  File testMidiFile;
  Pattern testPattern;

  MidiController(){
    println("MidiController");

    dir = new File("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader7/midi/");
    list = dir.list();
  }


  public void playingMidi(int index){
    Player player = new Player();
    // println("--------------------------------");
    // println("playingMidi : "+index);

    Pattern pattern = new Pattern(); 
      try {
         finalPattern = new Pattern();
        for (int i = 0; i < list.length; ++i) {
            isMidi = list[i].contains("mid");
            if(isMidi){
                if(i == index){
                  File midiFile = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader7/midi/"+list[i]));
                  pattern =  MidiFileManager.loadPatternFromMidi(midiFile);
                }
            }
        }

        StaccatoParser parser = new StaccatoParser();
        TemporalPLP plp = new TemporalPLP();
        parser.addParserListener(plp);
        parser.parse(pattern);
        partser.getTrackBeatTime();
        // Part 2. Send the events from Part 1, and play the original pattern with a delay
        CustomParser dpl = new CustomParser(); // Or your AnimationParserListener!
        plp.addParserListener(dpl);
        player.delayPlay(TEMPORAL_DELAY, pattern);
        plp.parse();

      } catch(Exception e) {
        println("erreur: "+e);
      }
  }
}


class CustomParser extends ParserListenerAdapter{

    CustomParser(){ 
      
    }

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


public class PhotoAnalizer {
	float[] blackPixels = new float[3];
	Capture cam;
	String[] cameras;
	PImage source;       // Source image
	PImage destination;  // Destination image
	float threshold = 127;
	boolean isCamDisplayed = true;
	boolean debug = true;

	public PhotoAnalizer (int cameraNumber, PApplet _that) {
		cameras = Capture.list();

		if (cameras == null) {
			if(debug){println("Failed to retrieve the list of available cameras, will try the default...");}
		}

		if (cameras.length == 0) {
			if(debug){println("There are no cameras available for capture.");}
			exit();
		} else {
			if(debug){
				println("Available cameras:");
				for (int i = 0; i < cameras.length; i++) {
			  		println(i + "" + cameras[i]);
				}
			}
			cam = new Capture(_that, cameras[cameraNumber]);
			cam.start();
		}
	}

	public void render(){
		 if (cam.available() == true) {
		    cam.read();
		  }
		  if(isCamDisplayed){
		    image(cam, 0, 0);
		  }
	}

	public void startAnalizise(){
	    cam.save("data/capture.jpg");
	    isCamDisplayed = false;

	    blackPixels[0] = 0;
	    blackPixels[1] = 0;
	    blackPixels[2] = 0;

	    source = loadImage("data/capture.jpg");
	    destination = createImage(source.width, source.height, RGB);

	    source.loadPixels();
	    destination.loadPixels();

	    for (int x = 0; x < source.width; x++) {
	      for (int y = 0; y < source.height; y++ ) {
	        int loc = x + y*source.width;
	        // Test the brightness against the threshold
	        if (brightness(source.pixels[loc]) < threshold) {
	          destination.pixels[loc]  = color(255);  // White
	        }  else {
	        	destination.pixels[loc]  = color(0);    // Black
	         	if(x < (source.width/3)){
	         		blackPixels[0] ++;
	         	}else if (x > (source.width/3) && x < ((source.width/3)*2)){
	         		blackPixels[1] ++;
	         	}else{
	         		blackPixels[2] ++;
	         	}
	        }
	      }
	    }

	    float base = source.width*source.height;

	    // We changed the pixels in destination
	    destination.updatePixels();
	    // Display the destination
	    image(destination,0,0);
	}

	public float[] getBlackPixels(){
		return blackPixels;
	}
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MidiReader7" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
