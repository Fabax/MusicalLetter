import processing.video.*;
Capture cam;
String[] cameras;
PImage source;       // Source image
PImage destination;  // Destination image
float threshold = 127;
boolean isCamDisplayed = true;

void setup() {
  size(900, 540);

  cameras = Capture.list();

  if (cameras == null) {
    println("Failed to retrieve the list of available cameras, will try the default...");
    cam = new Capture(this, 640, 480);
  } if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    println("Available cameras:");
    for (int i = 0; i < cameras.length; i++) {
      println(i + "" + cameras[i]);
    }

    // The camera can be initialized directly using an element
    // from the array returned by list():
    cam = new Capture(this, cameras[18]);
    // Or, the settings can be defined based on the text in the list
    //cam = new Capture(this, 640, 480, "Built-in iSight", 30);
    // Start capturing the images from the camera
    cam.start();
  }
}

void draw() {
  if (cam.available() == true) {
    cam.read();
  }
  if(isCamDisplayed){
    image(cam, 0, 0);  
  }
}

void keyPressed() {
  if(key == 'c' || key == 'C'){
    cam.save("data/capture.jpg");
    isCamDisplayed = false;
    int black = 0; 

     // We are going to look at both image's pixels
    source = loadImage("data/capture.jpg");  
    // The destination image is created as a blank image the same size as the source.
    destination = createImage(source.width, source.height, RGB);


    source.loadPixels();
    destination.loadPixels();
    
    for (int x = 0; x < source.width; x++) {
      for (int y = 0; y < source.height; y++ ) {
        int loc = x + y*source.width;
        // Test the brightness against the threshold
        if (brightness(source.pixels[loc]) > threshold) {
          destination.pixels[loc]  = color(255);  // White
        }  else {
          destination.pixels[loc]  = color(0);    // Black
          black ++;
        }
      }
    }

    float percentageBlack = black/(source.width*source.height);
    println("percentageBlack: "+black+"/"+source.width*source.height);

    // We changed the pixels in destination
    destination.updatePixels();
    // Display the destination
    image(destination,0,0);

  }
}
