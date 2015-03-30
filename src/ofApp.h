#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "FaceOsc.h"
#include "ofxXmlSettings.h"


class ofApp : public ofBaseApp, public FaceOsc {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
	
		void drawFbo();
	
		// OSC -----
		string host;
		int port;
	
		// CAMERA -----
		int camWidth, camHeight;
	
		ofVideoGrabber cam;
	
		// FACEOSC -----
		bool bDrawMesh;
	
		ofxFaceTracker tracker;
	
		// OF -----
		float scaleFactor;
	
		ofFbo rgbaFboFloat;
		int fadeAmnt;
};
