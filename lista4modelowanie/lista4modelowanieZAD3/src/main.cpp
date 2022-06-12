#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	//ofSetupOpenGL(1024,768, ofWindowMode::OF_FULLSCREEN);			// <-------- setup the GL context

	//ofGLFWWindowSettings settings;

	ofGLWindowSettings settings;
	settings.setGLVersion(4, 5);
	settings.setSize(1580, 1020); //1920 1080

	//ofSetDataPathRoot("../");
	ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
