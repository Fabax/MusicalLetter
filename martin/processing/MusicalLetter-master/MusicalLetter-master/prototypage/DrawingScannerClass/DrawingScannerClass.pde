import processing.video.*;
// Capture cam;
// String[] cameras;
// PImage source;       // Source image
// PImage destination;  // Destination image
// float threshold = 127;
// boolean isCamDisplayed = true;

PhotoAnalizer analizer; 

void setup() {
  size(900, 540, OPENGL);
  analizer = new PhotoAnalizer(0, this);
}

void draw() {
  analizer.render();
}

void keyPressed() {
  if(key == 'c' || key == 'C'){
    analizer.startAnalizise();

  }
}
