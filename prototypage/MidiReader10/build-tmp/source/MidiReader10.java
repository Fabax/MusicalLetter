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
import org.jfugue.rhythm.Rhythm; 
import processing.video.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MidiReader10 extends PApplet {

MidiController midiController;
PhotoAnalizer analizer; 
int[] r = new int[3];
boolean isLetterDetected = false;

public void setup() {
  size(900, 540);
  midiController = new MidiController();
  analizer = new PhotoAnalizer(3, this);
}

public void draw() {
  if(analizer.isLetterDetected()){
    isLetterDetected = true;
    //analizer.render();
    println("letter detected: ");
  }else{
    println("letter not detectes: ");
  }
}

public void keyPressed() {
  if (key == 'a' || key == 'A') {
    // midiController.assemblePattern();
    for (int i = 1; i <= 3; ++i) {
      //   midiController.playingMidi(i);
    }
  }
  if (key == 'c' || key == 'C') {
    analizer.runAnalize();
  }

  if (key == 'b' || key == 'B') {
    //midiController.playingMidi();
  }
}



















// import org.apache.commons.io.FilenameUtils;

public class MidiController {

  private static final long   TEMPORAL_DELAY = 0;
  Pattern finalPattern;


  MidiController(){
    println("MidiController");
  }


  public void playingMidi(){
    Player player = new Player();
     
      try {
        finalPattern = new Pattern();
        Rhythm rhythm = new Rhythm();
        //rhythm.addLayer("O..oO...O..oOO..");
        //rhythm.addLayer("..S...S...S...S.");
        //rhythm.addLayer("````````````````");
        //rhythm.addLayer("...............+");
        //finalPattern = rhythm.getPattern();

        File metalo = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader9/data/metalo.mid"));
        File tambour = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader9/data/tambour.mid"));
        File grelots = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader9/data/grelots.mid"));
        
        //rhythm.getLayers(metalo);
        
        //Pattern metaloPattern =  MidiFileManager.loadPatternFromMidi(metalo);
        //Pattern tambourPattern =  MidiFileManager.loadPatternFromMidi(tambour);
        //Pattern grelotsPattern =  MidiFileManager.loadPatternFromMidi(grelots);

       // finalPattern.add(metaloPattern);
        //metaloPattern.add(tambourPattern);
        //metaloPattern.add(grelotsPattern);
        
        finalPattern = rhythm.getPattern();

        StaccatoParser parser = new StaccatoParser();
        TemporalPLP plp = new TemporalPLP();
        parser.addParserListener(plp);
        parser.parse(finalPattern);
        // Part 2. Send the events from Part 1, and play the original pattern with a delay
        CustomParser dpl = new CustomParser(); // Or your AnimationParserListener!
        plp.addParserListener(dpl);
        player.delayPlay(TEMPORAL_DELAY, finalPattern);

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
  float blackPixels, ratio;
  Capture cam;
  String[] cameras;
  PImage source;       // Source image
  PImage destination;  // Destination image
  float threshold = 127;
  boolean isCamDisplayed = true;
  boolean debug = false;

  public PhotoAnalizer (int cameraNumber, PApplet _that) {
    cameras = Capture.list();


    if (cameras == null) {
      if (debug) {
        println("Failed to retrieve the list of available cameras, will try the default...");
      }
    }

    if (cameras.length == 0) {
      if (debug) {
        println("There are no cameras available for capture.");
      }
      exit();
    } else {
      if (debug) {
        println("Available cameras:");
        for (int i = 0; i < cameras.length; i++) {
          println(i + "" + cameras[i]);
        }
      }
      cam = new Capture(_that, cameras[cameraNumber]);
      cam.start();
    }
  }

  public void render() {
    if (cam.available() == true) {
      cam.read();
    }
    if (isCamDisplayed) {
      image(cam, 0, 0);
    }
  }
  
  public boolean isLetterDetected(){
  	boolean response = false;
  	runAnalize();
  	float ratio = getRatio();
  	if(ratio < 70){
  		response = true; 
  	}

  	return response;
  }

  public void runAnalize() {
   // cam.save("data/capture.jpg");
    isCamDisplayed = false;
    blackPixels = 0;
    ratio = 0;

    source = cam;
    source.loadPixels();

    destination = createImage(source.width, source.height, RGB);
    destination.loadPixels();  


    for (int x = 0; x < source.width; x++) {
      for (int y = 0; y < source.height; y++ ) {
        int loc = x + y*source.width;
        // Test the brightness against the threshold
        if (brightness(source.pixels[loc]) < threshold) {
          destination.pixels[loc]  = color(0);  // White
          blackPixels ++;
        } else {
          destination.pixels[loc]  = color(255);    // Black
        }
      }
    }

    float base = source.width*source.height;
    ratio = (blackPixels/base)*100;
    println("ratio : "+ratio);
    destination.updatePixels();
    if(debug){image(destination, 0, 0);}  
  }

  public float getRatio(){
  	return ratio;
  }

  public float getBlackPixels(){
  	return blackPixels;
  }
}

  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MidiReader10" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
