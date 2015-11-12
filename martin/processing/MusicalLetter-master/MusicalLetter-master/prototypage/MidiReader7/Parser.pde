class CustomParser extends ParserListenerAdapter {
  
  int nte;

  
  @Override
    public void onNoteParsed(Note note) {    
    //println("-----------------------------------");
    nte = note.getValue();
    //myPort.clear();

    if (nte == 72) {
      //myPort.write("1\n");
      myPort.write("1-2-3\n");
      //myPort.write("3\n");
    }
    if (nte == 76) {
      //myPort.write("2\n");
      //myPort.write("1-3\n\n");
      myPort.write("1-2-3\n");
      //myPort.write("3\n");
    }
    if (nte == 77) {
      //myPort.write("3\n");
      myPort.write("1-2-3\n");
      //myPort.write("1-3\n\n");
      //myPort.write("3\n");
    }

    /*if (nte == 72 || nte == 76 || nte == 77) {
     //myPort.write("1\n");
     //myPort.write("2\n");
     //myPort.write("3\n");
     }
     if (nte == 79 || nte == 83 || nte == 84) {
     //myPort.write("2\n");
     }
     if (nte == 86 || nte == 89 || nte == 91) {
     myPort.write("3\n");
     }*/

    println("note value: "+note.getValue());
    //println("note duration: "+note.getDuration());
    //println("note getToneString: "+note.getToneString(note.getValue()));
    //println("note getToneStringWithoutOctave: "+note.getToneStringWithoutOctave(note.getValue()));
  }

  @Override
    public void onTrackChanged(byte track) {
    // println("track: "+track);
  }

  @Override
    public void onMarkerParsed(java.lang.String marker) {
    // println("marker: "+marker);
  }

  @Override
    public void onNotePressed(Note note) {
    // println("note: "+note);
  }
}