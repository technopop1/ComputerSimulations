#include "ofApp.h"
#include <random> 


int S1cpu[W * H] = { 0 };
int S2cpu[W * H] = { 0 };
int W1cpu[W*H] = { 0 };
int W2cpu[W*H] = { 0 };
int Gcpu[W * H] = { 0 };
int SScpu[W * H] = { 0 };
std::mt19937 mtLos(time(NULL));
//--------------------------------------------------------------
void ofApp::setup() {

	shader.setupShaderFromFile(GL_COMPUTE_SHADER, "sand.glsl");
	shader.linkProgram();
	//ofSetFrameRate(30);
	std::mt19937 mt(time(NULL));
	std::uniform_int_distribution<int> random(0, 100);

	/*for (int i = 0; i < W; ++i) {
		Gcpu[i + H] = 1.0f;
		Gcpu[i + H - 1] = 1.0f;
		Gcpu[i + H - 2] = 1.0f;
	}*/

	S1cpu[W / 2 + H / 2 * W] = 1;//1.0f;
	//float S1cpu[W * H] = { 0 };
	A1.allocate(W * H * sizeof(int), S1cpu, GL_DYNAMIC_DRAW);
	A2.allocate(W * H * sizeof(int), S2cpu, GL_DYNAMIC_DRAW);
	W1.allocate(W * H * sizeof(int), S1cpu, GL_DYNAMIC_DRAW);
	W2.allocate(W * H * sizeof(int), S2cpu, GL_DYNAMIC_DRAW);
	G.allocate(W * H * sizeof(int), Gcpu, GL_DYNAMIC_DRAW);
	SS.allocate(W * H * sizeof(int), SScpu, GL_DYNAMIC_DRAW);
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	A2.bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	G.bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	W1.bindBase(GL_SHADER_STORAGE_BUFFER, 4);
	W2.bindBase(GL_SHADER_STORAGE_BUFFER, 5);
	SS.bindBase(GL_SHADER_STORAGE_BUFFER, 6);

	tekstura.allocate(W, H, GL_RGBA8);
	tekstura.bindAsImage(3, GL_WRITE_ONLY);
}

//--------------------------------------------------------------
void ofApp::update() {
	static int c = 1;
	/*static int dt = 0;
	if (dt > 1000000000) dt = 0;*/
	c = 1 - c;
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + c);
	A2.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + 1 - c);
	W1.bindBase(GL_SHADER_STORAGE_BUFFER, 4 + c);
	W2.bindBase(GL_SHADER_STORAGE_BUFFER, 4 + 1 - c);

	/*for (int i = 0; i < W; ++i) {
		Rcpu[i] = std::uniform_real_distribution<double>(0, 1)(mtLos);
	}
	R.allocate(W * sizeof(float), Rcpu, GL_DYNAMIC_DRAW);
	R.bindBase(GL_SHADER_STORAGE_BUFFER, 3);*/

	//int *data = A1.map<int>(GL_READ_ONLY);
	//int counter = 0;
	//for (int i = 0; i < W * H; ++i) {
	//	if (data[i] == 1) {
	//		counter++;
	//	}
	//}
	//A1.unmap();
	//std::cout << counter << "\n"; //  / W * H

	shader.begin();
	shader.setUniform1i("iStep", c);
	shader.setUniform1i("iLos", std::uniform_int_distribution<int>(5,25)(mtLos));
	shader.setUniform1f("iKey", material);
	shader.setUniform1i("iTime", int(ofGetElapsedTimef()));
	shader.setUniform4f("iMouse", glm::vec4(ofGetMouseX(), ofGetMouseY(), 0, ofGetMousePressed()));
	shader.setUniform3f("iResolution", ofGetBoxResolution());
	shader.dispatchCompute(W / 6, H / 6, 1);
	shader.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	tekstura.draw(0, 0);

}

void ofApp::keyPressed(int key)
{
	if (key == '0') {	// sand
		material = 0;
	}
	if (key == '1') {	// ground
		material = 1;
	}
	if (key == '2') {	// water
		material = 2;
	}
	if (key == '3') {
		material = 3;
	}
	if (key == '4') {
		material = 4;
	}
	if (key == '5') {
		material = 5;
	}
}


