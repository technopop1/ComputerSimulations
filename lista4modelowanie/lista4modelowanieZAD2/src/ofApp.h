#pragma once

#include "ofMain.h"

#define W 1920
#define H 1080

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	ofShader shader;
	ofTexture tekstura;

	ofBufferObject A1, B1, A2, B2;
	float A1cpu[W * H];
	float A2cpu[W * H];
	float B1cpu[W * H];
	float B2cpu[W * H];

};
