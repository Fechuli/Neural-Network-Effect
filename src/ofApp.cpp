#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//vidPlayer.load("hand.mp4");
	//vidPlayer.play();
	//vidPlayer.setLoopState(OF_LOOP_NORMAL);

	camW = 320;
	camH = 240;

	cam.setup(camW, camH);
	
	colorImg.allocate(camW, camH);
	grayImg.allocate(camW, camH);
	grayBg.allocate(camW, camH);
	grayDiff.allocate(camW, camH);
	
	gui.setup();
	gui.add(overallSpeed.setup("speed", 1, 0, 3));
	gui.add(noiseAmount.setup("noise", 1, 0, 3));
	gui.add(trail.setup("trail", 6.0, 0, 20));
	gui.add(threshold.setup("threshold", 80, 0, 255));
	gui.add(bLearnBackground.setup("capture bg", false));


	p.assign(1500, particle());

	for (int i = 0; i < p.size(); i++)
	{
		p[i].setup();
	}

	ofSetBackgroundAuto(false);

}

//--------------------------------------------------------------
void ofApp::update(){

	ofSetFrameRate(60);

	bool bNewFrame = false;
	cam.update();
	bNewFrame = cam.isFrameNew();

	//vidPlayer.update();
	//bNewFrame = vidPlayer.isFrameNew();

	if (bNewFrame == true)
	{
		//colorImg.setFromPixels(vidPlayer.getPixels());
		colorImg.setFromPixels(cam.getPixels());
		grayImg = colorImg;

		if (bLearnBackground == true)
		{
			grayBg = grayImg;
			bLearnBackground = false;
		}

		grayDiff.absDiff(grayBg, grayImg);
		grayDiff.threshold(threshold);

		contourFinder.findContours(grayDiff, 20, (camW * camH) * 0.9, 10, true);
	}

	vector<ofVec2f>blobPts;
	for (int i = 0; i < contourFinder.nBlobs; i++)
	{
		for (int j = 0; j < contourFinder.blobs[i].pts.size(); j++)
		{
			blobPts.push_back(contourFinder.blobs[i].pts[j] * ofGetWidth()/camW);
		}
	}

	for (int i = 0; i < p.size(); i++)
	{
		p[i].repel(blobPts);
		p[i].update(overallSpeed, noiseAmount);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){


	ofSetColor(0, 0, 0, trail);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	ofSetColor(ofRandom(70, 120),ofRandom(70, 70),ofRandom(70, 120), 255);


	for (int i = 0; i < p.size(); i++)
	{
		p[i].draw(1, p);

	}

	ofSetHexColor(0xffffff);
	colorImg.draw(20, 20);
	grayImg.draw(20 + camW, 20);
	grayBg.draw(20, 20+camH);
	grayDiff.draw(20 + camW, 20 + camH);


	ofFill();
	ofSetHexColor(0x333333);
	//ofDrawRectangle(360, 540, 320, 240);
	ofSetHexColor(0xffffff);

	contourFinder.draw(20 + camW, 20 + camH);

	gui.draw();

}

