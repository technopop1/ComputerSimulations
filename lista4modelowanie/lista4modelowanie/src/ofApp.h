#pragma once

#include "ofMain.h"

#define W 1920
#define H 1080

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		ofBufferObject A1;
		ofShader shader;
		ofTexture tekstura;

		float A1cpu[W * H] = { 0.0f };

		//static const int W = 1920;//1500;
		//static const int H = 1080;
		
		//float A1cpu[W * H] = {0.0f};
		
};
