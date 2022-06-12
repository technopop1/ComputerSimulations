#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {

	shader.setupShaderFromFile(GL_COMPUTE_SHADER, "secondShader.glsl");
	shader.linkProgram();

	tekstura.allocate(W, H, GL_RGBA8);
	tekstura.bindAsImage(4, GL_WRITE_ONLY);

	//A1.allocate(W * H * sizeof(float), A1cpu, GL_DYNAMIC_DRAW);
	//A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0);


	// initialize
	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
		{
			int idx = x + y * W;
			A1cpu[idx] = 1.0;
			A2cpu[idx] = 1.0;
			if (rand() / float(RAND_MAX) < 0.000021)
				B1cpu[idx] = 1.0; else B1cpu[idx] = 0.0;
			B2cpu[idx] = 0.0;
		}
	// allocate buffers on GPU side
	A1.allocate(W * H * sizeof(float), A1cpu, GL_STATIC_DRAW);
	A2.allocate(W * H * sizeof(float), A2cpu, GL_STATIC_DRAW);
	B1.allocate(W * H * sizeof(float), B1cpu, GL_STATIC_DRAW);
	B2.allocate(W * H * sizeof(float), B2cpu, GL_STATIC_DRAW);

	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	A2.bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	B1.bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	B2.bindBase(GL_SHADER_STORAGE_BUFFER, 3);

}

//--------------------------------------------------------------
void ofApp::update() {
	// bindings (ping pong)
	static int c = 1;
	c = 1 - c;

	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + c);
	A2.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + 1 - c);
	B1.bindBase(GL_SHADER_STORAGE_BUFFER, 2 + c);
	B2.bindBase(GL_SHADER_STORAGE_BUFFER, 2 + 1 - c);

	// run shader (Gray Scott)
	shader.begin();
	shader.dispatchCompute(W / 20, H / 20, 1);
	shader.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	tekstura.draw(0, 0);

}
