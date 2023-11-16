#include "particle.h"

particle::particle()
{

}

void particle::setup()
{
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();

	vel.x = ofRandom(-4, 4);
	vel.y = ofRandom(-4, 4);

	frc = ofVec2f(0, 0);

	uniqueVal.x = ofRandom(-1000, 1000);
	uniqueVal.y = ofRandom(-1000, 1000);

	size = ofRandom(0.5, 1.5);

	drag = ofRandom(0.97, 0.99);
}

void particle::update(float speed, float noise)
{
	frc.x = ofSignedNoise(uniqueVal.x, ofGetElapsedTimeMillis());
	frc.y = ofSignedNoise(uniqueVal.y, ofGetElapsedTimeMillis());

	frc *= noise;

	vel *= drag;

	vel -= repelFrc;

	vel += frc;
	//---------------------------------------

	if (pos.x + vel.x > ofGetWidth())
	{
		pos.x -= ofGetWidth();
	}
	else if (pos.x + vel.x < 0)
	{
		pos.x += ofGetWidth();
	}

	//---------------------------------------

	if (pos.y + vel.y > ofGetHeight())
	{
		pos.y -= ofGetHeight();
	}
	else if (pos.y + vel.y < 0)
	{
		pos.y += ofGetHeight();
	}

	pos += vel * speed;


}

void particle::draw(float sizeDot, vector<particle>& particles)
{

	ofDrawCircle(pos.x, pos.y, size * sizeDot);
	ofSetColor(255, 255, 255, 1);

	for (int i = 0; i < particles.size(); i++)
	{
		if (&particles[i] != this)
		{
			float dist = pos.distance(particles[i].pos);

			if (dist < 150)
			{
				ofDrawLine(pos.x, pos.y, particles[i].pos.x, particles[i].pos.y);
			}
		}
	}
}

void particle::repel(vector<ofVec2f> repelPt)
{
	repelFrc.set(0, 0);
	for (int i = 0; i < repelPt.size(); i++)
	{
		float dist = pos.distance(repelPt[i]);

		if (dist < 150) {
			ofVec2f newRepelPt;
			newRepelPt = repelPt[i] - pos;
			repelFrc += newRepelPt * 0.0001;
		}
	}
}
