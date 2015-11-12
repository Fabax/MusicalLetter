class CustomParser extends ParserListenerAdapter{
    AudioPlayer minimePlayer;
    Minim minim;

    CustomParser(AudioPlayer _minimePlayer){ 
      minimePlayer = _minimePlayer;
    }

    @Override
    public void onNoteParsed(Note note) {
      if(note.isFirstNote()){
        minimePlayer.play();
      }
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
