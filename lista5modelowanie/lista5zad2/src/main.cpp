#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(4, 5);
	settings.setSize(1920, 1080); //1920 1080

	//ofSetDataPathRoot("../");
	ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
