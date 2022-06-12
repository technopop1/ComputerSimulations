#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	shader.setupShaderFromFile(GL_COMPUTE_SHADER, "firstShader.glsl");
	shader.linkProgram();
	
	//float A1cpu[W * H] = { 0 };
	A1.allocate(W * H * sizeof(float), A1cpu, GL_DYNAMIC_DRAW);
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0);

	tekstura.allocate(W, H, GL_RGBA8);
	tekstura.bindAsImage(1, GL_WRITE_ONLY);
}

//--------------------------------------------------------------
void ofApp::update(){
	shader.begin();
	shader.dispatchCompute(W/20, H/20, 1);
	shader.end();
}

//--------------------------------------------------------------
void ofApp::draw(){

	tekstura.draw(0, 0);

}
