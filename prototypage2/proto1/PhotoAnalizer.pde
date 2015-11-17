import processing.video.*;

public class PhotoAnalizer {
  float blackPixels,ratio;
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

  public void startAnalizise() {
    cam.save("data/capture.jpg");
    isCamDisplayed = false;

    blackPixels = 0;
    ratio = 0;

    source = loadImage("data/capture.jpg");
    destination = createImage(source.width, source.height, RGB);

    source.loadPixels();
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
    println("ratio "+ratio);

    destination.updatePixels();
    image(destination, 0, 0);
  }

  public float getBlackPixels() {
    return blackPixels;
  }

  public float getRatio() {
    return blackPixels;
  }
}

