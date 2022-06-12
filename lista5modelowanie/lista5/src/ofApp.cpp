#include "ofApp.h"
#include <random>
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup() {

	densityData.open("data3.txt", std::ios::out);// fstream::out | fstream::app);

	shader.setupShaderFromFile(GL_COMPUTE_SHADER, "GameOfLifeSHADER.glsl");
	shader.linkProgram();
	ofSetFrameRate(60);
	std::mt19937 mt(time(NULL));
	std::uniform_int_distribution<int> random(0, 100);

	for (int i = 0; i < W*H; ++i) {
		//for (int j = 0; j < H; ++j) {
		if (random(mt) < 60) {
			A1cpu[i] = 255.0f;
			A2cpu[i] = 255.0f;
		}
				//A1cpu[i][j] = 255.0f;
		//}
	}

	//float A1cpu[W * H] = { 0 };
	A1.allocate(W * H * sizeof(float), A1cpu, GL_DYNAMIC_DRAW);
	A2.allocate(W * H * sizeof(float), A2cpu, GL_DYNAMIC_DRAW);
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	A2.bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	tekstura.allocate(W, H, GL_RGBA8);
	tekstura.bindAsImage(1, GL_WRITE_ONLY);
}

//--------------------------------------------------------------
void ofApp::update() {


	static int c = 1;
	c = 1 - c;
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + c);
	//A2.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + 1 - c);

	shader.begin();
	shader.dispatchCompute(W / 20, H / 20, 1);
	shader.end();

	dataA1 = A1.map<float>(GL_READ_ONLY);
	//dataA2 = A2.map<float>(GL_READ_ONLY);
	for (int idx = 0; idx < W * H; idx++) {
		if (dataA1[idx] == 255.0f)
			densityA1 += 1;
		//densityA2 = densityA2 + dataA2[idx];
	}
	densityA1 = densityA1 / float(W * H);
	//densityA2 = densityA2 / float(W * H);

	densityData << densityA1  << "\n";
	//}
	//A2.unmap();
	A1.unmap();
}

//--------------------------------------------------------------
void ofApp::draw() {

	tekstura.draw(0, 0);

}
