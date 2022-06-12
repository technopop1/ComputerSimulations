#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {

	//ofGLFWWindowSettings settings;

	ofGLWindowSettings settings;
	settings.setGLVersion(4, 5);
	settings.setSize(1920, 1080);


	ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
