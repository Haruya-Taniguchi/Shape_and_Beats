#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //音関係の設定
    int bufferSize = 256;
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    bufferCounter    = 0;
    drawCounter        = 0;
    smoothedVol     = 0.0;
    scaledVol        = 0.0;
    
    soundStream.printDeviceList();
    ofSoundStreamSettings settings;
    auto devices = soundStream.getDeviceList();
    settings.setInDevice(devices[2]);//ここを書き換えて入力を切り替える
    
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = bufferSize;
    
    soundStream.setup(settings);
    
    //GL系の設定
    ofSetFrameRate(60);
    ofSetBackgroundColor(bgColor);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //shader
    shader.load("shaders/myShadeFlat");

    //カメラ
    cam.setNearClip(0);
    cam.setFarClip(1500);

    //bunny
    bunny.loadModel("bunny.obj", 10);
    bunny.setScale(128.0, 128.0, 128.0);

    //IcoSphere
    icoSphere.setPosition(pos);
    icoSphere.setResolution(2);
    icoSphere.setRadius(256);
    //Box
    box.setResolution(8);
    //Cylinder
    cylinder.set(128,256);
    cylinder.setResolution(20, 13, 4);
    //Sphere
    sphere.setRadius(256);
    sphere.setResolution(32);

    //メッシュをロード
    vboMesh = icoSphere.getMesh();
    tempVboMesh = vboMesh;
    pos = glm::vec3(0.0,0.0,0.0);

    //gui
    gui.setup();
    gui.add(lightDirSlider.setup("lightDir",lightDirection,glm::vec3(-1.0,-1.0,-1.0),glm::vec3(1.0,1.0,1.0)));
    gui.add(effect.setup("effect",1.0,0.0,2.0));
    gui.add(bgColorSlider.setup("bgColor", ofColor(6, 227, 208,255), ofColor(0, 0), ofColor(255, 255)));
    gui.add(vertColorSlider.setup("vertColor", ofColor(255, 48, 131, 255), ofColor(0, 0), ofColor(255, 255)));
}

//--------------------------------------------------------------
void ofApp::update(){
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }

    time = ofGetElapsedTimef();
    lightDirection = lightDirSlider;
    bgColor = bgColorSlider;
    vertColor = vertColorSlider;

    // debug
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(bgColorSlider);
    cam.begin();
    shader.begin();
    
    eyeDirection = cam.getLookAtDir();

    // model Matrix
    ofMatrix4x4 modelMatrix;
    modelMatrix.translate(pos);
    modelMatrix.rotate(time*10, 0.0, 1.0, 0.0);

    // view Matrix
    ofMatrix4x4 viewMatrix;
    viewMatrix = ofGetCurrentViewMatrix();
    
    // projection Matrix
    ofMatrix4x4 projectionMatrix;
    projectionMatrix = cam.getProjectionMatrix();
    
    // mvp Matrix
    ofMatrix4x4 mvpMatrix;
    mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
    ofMatrix4x4 invMatrix;
    invMatrix = mvpMatrix.getInverse();

    shader.setUniformMatrix4f("model", modelMatrix);
    shader.setUniformMatrix4f("view", viewMatrix);
    shader.setUniformMatrix4f("projection", projectionMatrix);
    shader.setUniformMatrix4f("mvpMatrix", mvpMatrix);
    shader.setUniformMatrix4f("invMatrix", invMatrix);
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform3f("lightDirection",lightDirection);
    shader.setUniform3f("eyeDirection", eyeDirection);
    shader.setUniform4f("ambientColor", ambientColor);
    shader.setUniform4f("bgColor", glm::vec4(bgColor.r/255.0,bgColor.g/255.0,bgColor.b/255.0,bgColor.a/255.0));
     
    vboMesh.clearColors();
    //vboMesh.clearNormals();
    for(int i=0; i<vboMesh.getVertices().size(); i++){
        vboMesh.addColor(vertColor);
        vboMesh.setVertex(i,tempVboMesh.getVertices()[i]+
        tempVboMesh.getVertices()[i]*(ofNoise(tempVboMesh.getVertices()[i]+glm::vec3(time))
        *effect*scaledVol));
        //vboMesh.addNormal(vboMesh.getNormals()[i]);
    }
    
    vboMesh.draw();

    shader.end();
    cam.end();
    gui.draw();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case '0':
            mode = 0;
            vboMesh = bunny.getMesh(0);
            tempVboMesh = vboMesh;
            pos = glm::vec3(-vboMesh.getCentroid());
        break;
        case '1':
            vboMesh = sphere.getMesh();
            tempVboMesh = vboMesh;
            pos = glm::vec3(0.0,0.0,0.0);
        break;
        case '2':
            vboMesh = icoSphere.getMesh();
            tempVboMesh = vboMesh;
            pos = glm::vec3(0.0,0.0,0.0);
        break;
        case '3':
            vboMesh = cylinder.getMesh();
            tempVboMesh = vboMesh;
            pos = glm::vec3(0.0,0.0,0.0);
        break;
        case '4':
            vboMesh = box.getMesh();
            tempVboMesh = vboMesh;
            pos = glm::vec3(0.0,0.0,0.0);
        break;
        case 'a':
            shader.load("shaders/gouraud");
        break;
        case 'b':
            shader.load("shaders/phong");
        break;
        case 'c':
            shader.load("shaders/flat");
        break;
        case 'd':
            shader.load("shaders/myShade");
        break;
        case 'e':
            shader.load("shaders/myShadeFlat");
        break;
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (size_t i = 0; i < input.getNumFrames(); i++){
        left[i]        = input[i*2]*0.5;
        right[i]    = input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}