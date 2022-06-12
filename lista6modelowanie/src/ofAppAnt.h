#pragma once

#include "ofMain.h"

#define W 1920
#define H 980

class ofAppAnt : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	std::vector<int> Ant{ W / 4, H / 2, 0 };
	ofBufferObject A1, A2, A3;// , A4;
	ofShader shader;
	ofTexture tekstura;

};
