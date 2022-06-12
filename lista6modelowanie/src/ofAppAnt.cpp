#include "ofAppAnt.h"
#include <random>


float A1cpuAnt[W * H] = { 0.0f };
float A2cpuAnt[W * H] = { 0.0f };
float A3cpuAnt[W * H] = { 0.0f };
const int nSizeCheck = 300;
float movesCopy[nSizeCheck] = { 0.0f };
int counterMove = 0;
int timeCounter = 0;
//float A4cpuAnt[W * H] = { 0.0f };
std::mt19937 mt(time(NULL));
//--------------------------------------------------------------
void ofAppAnt::setup() {

	shader.setupShaderFromFile(GL_COMPUTE_SHADER, "ant.glsl");
	shader.linkProgram();
	//ofSetFrameRate(30);
	//std::mt19937 mt(time(NULL));
	std::uniform_int_distribution<int> random(0, 100);

	/*for (int i = 0; i < W*H; ++i) {
		if (random(mt) < 15) {
			A1cpu[i] = 1.0f;
			A2cpu[i] = 1.0f;
		}
	}*/

	//A1cpuAnt[W / 2 + H / 2 * W] = 1.0f;
	//A2cpuAnt[W / 2 + H / 2 * W] = 1.0f;
	//A3cpuAnt[W / 2 + H / 2 * W] = 1.0f;
	Ant[2] = std::uniform_int_distribution<int>(0, 3)(mt);

	A1.allocate(W * H * sizeof(float), A1cpuAnt, GL_DYNAMIC_DRAW);
	A2.allocate(W * H * sizeof(float), A2cpuAnt, GL_DYNAMIC_DRAW);
	A3.allocate(W * H * sizeof(float), A3cpuAnt, GL_DYNAMIC_DRAW);
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	A2.bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	A3.bindBase(GL_SHADER_STORAGE_BUFFER, 2);

	tekstura.allocate(W, H, GL_RGBA8);
	tekstura.bindAsImage(1, GL_WRITE_ONLY);

}

int per(int x, int nx) {
	if (x < 0) x += nx;
	if (x >= nx) x -= nx;
	return x;
}
//--------------------------------------------------------------
void ofAppAnt::update() {

	static int c = 1;
	c = 1 - c;
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 1);// 0 + c);
	//A2.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + 1 - c);
	//A3.bindBase(GL_SHADER_STORAGE_BUFFER, 2);
		
	float* dataA1 = A1.map<float>(GL_READ_ONLY);

	if (dataA1[Ant[0] + Ant[1] * W] == 1.0f) {
		Ant[2] = per(Ant[2] + 1, 4);	// w prawo
	}
	else {
		Ant[2] = per(Ant[2] - 1, 4);	// w lewo
	}
	A1.unmap();
	
	if (counterMove >= nSizeCheck) counterMove = 0;
	else movesCopy[ counterMove++ ] = 1 + Ant[2];
	for (int faze = nSizeCheck/4; faze < nSizeCheck/2; ++faze) {
		bool check = false;
		int sameDigitsChain = 0;

		for (int i = 0; i < faze; ++i) {
			if (movesCopy[0 + i] == movesCopy[faze + i]) {
				sameDigitsChain++;
			}
		}
		if (sameDigitsChain == faze) {
			check = true;
		}
		if (check == true) { std::cout << "AUTOSTRADA zaczela sie po " << timeCounter << " krokach\n"; faze = nSizeCheck / 2;}
	}
	shader.begin();
	shader.setUniform4f("iMouse", glm::vec4(ofGetMouseX(), ofGetMouseY(), 0, ofGetMousePressed()));
	shader.setUniform3f("iResolution", ofGetBoxResolution());
	shader.setUniform2f("iAnt", glm::vec2(Ant[0], Ant[1]));
	shader.dispatchCompute(W / 20, H / 20, 1);
	shader.end();

	if (Ant[2] == 0) { Ant[0] = per(Ant[0] + 1, W / 2); }
	if (Ant[2] == 1) { Ant[1] = per(Ant[1] + 1, H); }
	if (Ant[2] == 2) { Ant[0] = per(Ant[0] - 1, W / 2); }
	if (Ant[2] == 3) { Ant[1] = per(Ant[1] - 1, H); }

	timeCounter++;
}

//--------------------------------------------------------------
void ofAppAnt::draw() {

	tekstura.draw(0, 0);

}
