#include "ofMain.h"
#include "ofApp.h"
#include "ofAppAnt.h"

//========================================================================
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(4, 5);
	settings.setSize(1920, 980); //1920 1080

	ofCreateWindow(settings);
	ofRunApp(new ofApp());
	//ofRunApp(new ofAppAnt());

}