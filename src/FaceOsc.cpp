#include "FaceOsc.h"

void FaceOsc::sendFaceOsc(ofxFaceTracker& tracker) {
    clearBundle();
    
    if(tracker.getFound()) {
        addMessage("/found", 1);
        
        ofVec2f position = tracker.getPosition();
        addMessage("/pose/position", position);
				addMessage("/pose/position/x", ofMap(position.x, 0, ofGetWindowWidth(), 0.0, 1.0, true));
				addMessage("/pose/position/y", ofMap(position.y, 0, ofGetWindowHeight(), 0.0, 1.0, true));
			
        addMessage("/pose/scale", ofMap(tracker.getScale(), 0, 10, 0.0, 1.0, true));
			
        ofVec3f orientation = tracker.getOrientation();
        addMessage("/pose/orientation", orientation);
			
				addMessage("/pose/orientation/yaw", ofMap(orientation.x, -1.0, 1.0, 0.0, 1.0, true));
				addMessage("/pose/orientation/pitch", ofMap(orientation.y, -1.0, 1.0, 0.0, 1.0, true));
				addMessage("/pose/orientation/roll", ofMap(orientation.z, -1.0, 1.0, 0.0, 1.0, true));
			
			
        addMessage("/gesture/mouth/width", ofMap(tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH), 10., 20., 0., 1., true));
        addMessage("/gesture/mouth/height", ofMap(tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT), 0., 9., 0., 1., true));
			
        addMessage("/gesture/eyebrow/left", ofMap(tracker.getGesture(ofxFaceTracker::LEFT_EYEBROW_HEIGHT), 5, 10, 0.0, 1.0, true));
        addMessage("/gesture/eyebrow/right", ofMap(tracker.getGesture(ofxFaceTracker::RIGHT_EYEBROW_HEIGHT), 5, 10, 0.0, 1.0, true));
			
			
        addMessage("/gesture/eye/left", ofMap(tracker.getGesture(ofxFaceTracker::LEFT_EYE_OPENNESS), 0, 5, 0.0, 1.0, true));
        addMessage("/gesture/eye/right", ofMap(tracker.getGesture(ofxFaceTracker::RIGHT_EYE_OPENNESS), 0, 5, 0.0, 1.0, true));
			
        addMessage("/gesture/jaw", ofMap(tracker.getGesture(ofxFaceTracker::JAW_OPENNESS), 20, 30, 0.0, 1.0, true));
			
        addMessage("/gesture/nostrils", ofMap(tracker.getGesture(ofxFaceTracker::NOSTRIL_FLARE), 5, 10, 0.0, 1.0, true));
			
    } else {
        addMessage("/found", 0);
    }
    
    sendBundle();
}

void FaceOsc::clearBundle() {
	bundle.clear();
}

void FaceOsc::addMessage(string address, ofVec3f data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data.x);
	msg.addFloatArg(data.y);
	msg.addFloatArg(data.z);
	bundle.addMessage(msg);
}

void FaceOsc::addMessage(string address, ofVec2f data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data.x);
	msg.addFloatArg(data.y);
	bundle.addMessage(msg);
}

void FaceOsc::addMessage(string address, float data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data);
	bundle.addMessage(msg);
}

void FaceOsc::addMessage(string address, int data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addIntArg(data);
	bundle.addMessage(msg);
}

void FaceOsc::sendBundle() {
	osc.sendBundle(bundle);
}
