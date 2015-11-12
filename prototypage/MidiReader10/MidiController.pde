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
        Rhythm rhythm = new Rhythm()
        .addLayer("O..oO...O..oOO..")
        .addLayer("..S...S...S...S.")
        .addLayer("````````````````")
        .addLayer("...............+");
        finalPattern = rhythm.getPattern()
    new Player().play(finalPattern);
 //       File metalo = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader9/data/metalo.mid"));
 //       File tambour = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader9/data/tambour.mid"));
 //       File grelots = new File(dataPath("/Users/fbonnamy/Documents/pro/WIW/MusicalLetter/prototypage/MidiReader9/data/grelots.mid"));
        
//        Pattern metaloPattern =  MidiFileManager.loadPatternFromMidi(metalo);
//        Pattern tambourPattern =  MidiFileManager.loadPatternFromMidi(tambour);
//        Pattern grelotsPattern =  MidiFileManager.loadPatternFromMidi(grelots);

       // finalPattern.add(metaloPattern);
        //metaloPattern.add(tambourPattern);
        //metaloPattern.add(grelotsPattern);

        StaccatoParser parser = new StaccatoParser();
        TemporalPLP plp = new TemporalPLP();
        parser.addParserListener(plp);
        parser.parse(metaloPattern);
        // Part 2. Send the events from Part 1, and play the original pattern with a delay
        CustomParser dpl = new CustomParser(); // Or your AnimationParserListener!
        plp.addParserListener(dpl);
        player.delayPlay(TEMPORAL_DELAY, metaloPattern,tambourPattern );
        plp.parse();

      } catch(Exception e) {
        println("erreur: "+e);
      }
  }
}


