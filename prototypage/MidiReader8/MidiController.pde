// import org.jfugue.player.Player;
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

    dir = new File("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader8/midi/");
    list = dir.list();
  }


  public void playingMidi(int index, AudioPlayer minimePlayer){
    // Player player = new Player();
    // println("--------------------------------");
    // println("playingMidi : "+index);

    Pattern pattern = new Pattern(); 
      try {
         finalPattern = new Pattern();
        for (int i = 0; i < list.length; ++i) {
            isMidi = list[i].contains("mid");
            if(isMidi){
                if(i == index){
                  File midiFile = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader8/midi/"+list[i]));
                  pattern =  MidiFileManager.loadPatternFromMidi(midiFile);
                }
            }
        }

        StaccatoParser parser = new StaccatoParser();
        TemporalPLP plp = new TemporalPLP();
        parser.addParserListener(plp);
        parser.parse(pattern);
        // Part 2. Send the events from Part 1, and play the original pattern with a delay
        CustomParser dpl = new CustomParser(minimePlayer); // Or your AnimationParserListener!
        plp.addParserListener(dpl);
        // player.delayPlay(TEMPORAL_DELAY, pattern);
        plp.parse();

      } catch(Exception e) {
        println("erreur: "+e);
      }
  }
}


