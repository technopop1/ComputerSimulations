#pragma once

#include "ofMain.h"

#define W 1920
#define H 980

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	ofBufferObject A1, A2, G, W1, W2, SS;
	ofShader shader;
	ofTexture tekstura;

	float material = 0;
	void keyPressed(int key) override;
};
