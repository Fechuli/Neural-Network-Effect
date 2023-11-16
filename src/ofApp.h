#pragma once

#include "ofMain.h"
#include "particle.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		vector<particle>p;
		
		ofxPanel gui;
		ofxFloatSlider overallSpeed;
		ofxFloatSlider noiseAmount;
		ofxFloatSlider trail;

		//ofVideoPlayer vidPlayer;
		ofVideoGrabber cam;

		ofxCvColorImage colorImg;
		ofxCvGrayscaleImage grayImg;
		ofxCvGrayscaleImage grayBg;
		ofxCvGrayscaleImage grayDiff;

		ofxCvContourFinder contourFinder;

		ofxIntSlider threshold;
		ofxToggle bLearnBackground;

		int camW;
		int camH;
	
};
