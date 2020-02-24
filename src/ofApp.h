#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

        void audioIn(ofSoundBuffer & input);
		
		ofSoundStream soundStream;
		vector <float> left;
        vector <float> right;
        vector <float> volHistory;
		int     bufferCounter;
        int     drawCounter;
		float smoothedVol;
        float scaledVol;

		ofEasyCam cam;
		ofShader shader;
    	ofVboMesh vboMesh;
		ofVboMesh tempVboMesh;

		glm::vec3 pos;
		ofIcoSpherePrimitive icoSphere;
		ofSpherePrimitive sphere;
		ofBoxPrimitive box = ofBoxPrimitive(256, 256, 256);
		ofCylinderPrimitive cylinder;
		ofxAssimpModelLoader bunny;

		int mode = 0;

		float time;
		glm::vec3 lightDirection = glm::vec3(1.0,1.0,-0.01);
		glm::vec4 ambientColor = glm::vec4(0.1,0.1,0.1,1.0);
		glm::vec3 eyeDirection = glm::vec3(0.0, 0.0, 10.0);
		ofColor bgColor = ofColor(6,227,208,255);
		ofColor vertColor = ofColor(255, 48, 131, 255);

		ofxPanel gui;
    	ofxVec3Slider lightDirSlider;
		ofxFloatSlider effect;
		ofxColorSlider bgColorSlider, vertColorSlider;
};
