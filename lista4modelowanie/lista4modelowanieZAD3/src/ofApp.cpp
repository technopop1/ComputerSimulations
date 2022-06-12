#include "ofApp.h"
#include <random>

//--------------------------------------------------------------
void ofApp::setup() {

	shader.setupShaderFromFile(GL_COMPUTE_SHADER, "GameOfLifeSHADER.glsl");
	shader.linkProgram();

	std::mt19937 mt(time(NULL));
	std::uniform_int_distribution<int> random(0, 100);

	for (int i = 0; i < W*H; ++i) {
		//for (int j = 0; j < H; ++j) {
			if (random(mt) < 80)
				A1cpu[i] = 255.0f;
				//A1cpu[i][j] = 255.0f;
		//}
	}
	memcpy(A2cpu, A1cpu, sizeof(A1cpu));

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


	//memcpy(A1cpu, A2cpu, sizeof(A2cpu));

	//for (int i = 0; i < W*H; i++) {
	//		
	//	int neighborsAlive = 0;
	//	if (A1cpu[(i + 1	 + W) % W] == 255.0f) neighborsAlive += 1;	//	RIGHT
	//	if (A1cpu[(i - 1	 + W) % W] == 255.0f) neighborsAlive += 1;	//	LEFT
	//	if (A1cpu[(i + W	 + W) % W] == 255.0f) neighborsAlive += 1;	//	BOTTOM
	//	if (A1cpu[(i - W	 + W) % W] == 255.0f) neighborsAlive += 1;	//	TOP
	//	if (A1cpu[(i + W + 1 + W) % W] == 255.0f) neighborsAlive += 1;	//	RIGHT-BOTTOM
	//	if (A1cpu[(i - W + 1 + W) % W] == 255.0f) neighborsAlive += 1;	//	RIGHT-TOP
	//	if (A1cpu[(i + W - 1 + W) % W] == 255.0f) neighborsAlive += 1;	//	LEFT-BOTTOM
	//	if (A1cpu[(i - W - 1 + W) % W] == 255.0f) neighborsAlive += 1;	//	LEFT-TOP

	//	if (((neighborsAlive == 2 || neighborsAlive == 3) && A1cpu[i] == 1) || (neighborsAlive == 3 && A1cpu[i] == 0))
	//		A2cpu[i] = 255.0f;
	//	else
	//		A2cpu[i] = 0.0f;

	//}

	//A1.allocate(W * H * sizeof(float), A1cpu, GL_DYNAMIC_DRAW);
	static int c = 1;
	c = 1 - c;
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + c);
	A2.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + 1 - c);

	shader.begin();
	shader.dispatchCompute(W / 20, H / 20, 1);
	shader.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	tekstura.draw(0, 0);

}
