#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	
	// OSC -----
	host = "128.237.195.104";
	port = 9000;
	
	osc.setup(host, port);
	
	// CAMERA -----
	
	camWidth = 640;
	camHeight = 480;
	
	vector<ofVideoDevice> devices = cam.listDevices();
	for (int i = 0; i < devices.size(); i++) {
		cout << devices[i].id << ": " << devices[i].deviceName;
    if (devices[i].bAvailable) {
			cout << endl;
		} else {
			cout << " - unavailable" << endl;
		}
	}
	
	cam.setDeviceID(0);
	cam.initGrabber(camWidth, camHeight);
	
	// SETTINGS -----
	bDrawMesh = false;
	
	scaleFactor = 2.;
	
	tracker.setRescale(1.);
	tracker.setIterations(5);
	tracker.setClamp(2);
	tracker.setTolerance(.01);
	tracker.setAttempts(2);
	tracker.setup();
	
	ofBackground(30, 20, 10);
	
	// OPENGL -----
	#ifdef TARGET_OPENGLES
		rgbaFboFloat.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA);
		ofLogWarning("ofApp") << "GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
	#else
        rgbaFboFloat.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB);
	#endif
	
	rgbaFboFloat.begin();
	ofClear(255, 255, 255, 0);
	rgbaFboFloat.end();

}

//--------------------------------------------------------------
void ofApp::update(){

	cam.update();
	
	if (cam.isFrameNew()) {
	
		tracker.update(toCv(cam));
		sendFaceOsc(tracker);
		
	}
	
	rgbaFboFloat.begin();
	drawFbo();
	rgbaFboFloat.end();
	
}

//--------------------------------------------------------------
void ofApp::drawFbo(){

//	fadeAmnt = 80;
//	
//	ofFill();
//	ofSetColor(255, 255, 255, fadeAmnt);
//	ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	ofClear(0, 0, 0, 255);
	
	if (bDrawMesh) {
	
		ofSetColor(215, 255, 10);
//		ofSetColor(255, 255, 255);
		
		
		ofTranslate((ofGetWindowWidth() / 2) - (camWidth * scaleFactor) / 2, (ofGetWindowHeight() / 2) - (camHeight * scaleFactor) / 2);
		ofScale(scaleFactor, scaleFactor);
		
//		ofSetLineWidth(2);
//		tracker.getImageMesh().drawWireframe();
		
		ofSetLineWidth(5);
		tracker.draw();

		ofSetColor(255, 50, 50);
		ofSetLineWidth(7);
		tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH).draw();
		tracker.getImageFeature(ofxFaceTracker::INNER_MOUTH).draw();
		
		ofSetColor(215, 255, 10);
		ofNoFill();
		ofSetLineWidth(3);
		ofCircle(tracker.getImageFeature(ofxFaceTracker::LEFT_EYE).getCentroid2D()[0], tracker.getImageFeature(ofxFaceTracker::LEFT_EYE).getCentroid2D()[1], 3);
		ofCircle(tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE).getCentroid2D()[0], tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE).getCentroid2D()[1], 3);
		
		
		
	} else {
		ofDrawBitmapString("Not Tracking. Press SPACEBAR to track.", ofPoint(10, 10));
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255, 255, 255);
	rgbaFboFloat.draw(0, 0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
  case ' ':
    bDrawMesh = !bDrawMesh;
    break;
}

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
