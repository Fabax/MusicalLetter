import processing.video.*;

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
