#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    frequency = 80;
    envelope.setAttack(100);
    envelope.setDecay(5);
    envelope.setSustain(1);
    envelope.setRelease(1000);
    beat.load(ofToDataPath("piano.wav"));
    check  = true;
    inputManager = new InputManager();
    reverb = new Reverb();
    outputManager = new OutputManager();
    inputManager -> addNewInput(currentsample); // add an audio source to the inputManager
    gui = new Gui(*reverb,*inputManager, *outputManager); // reference the managers in the gui
    gui->setup("reverb");
    ofSoundStreamSetup(2, 2, this, sampleRate, buffersize, 4);
}

//--------------------------------------------------------------
void ofApp::update()
{
    gui->update(ofGetMouseX(), ofGetMouseY());
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(95);
    gui->draw();
}
// create audioThread
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++){
        currentsample = beat.play(); // get the next bit of data from the sample
        inputManager->run();
        reverb->run();
        outputManager->run(outputSample);
        mix.stereo(outputSample * 0.6, outputs, 0.5);
        
        // output the audio
        output[i * nChannels]     = outputs[0];
        output[i * nChannels + 1] = outputs[0];
        outputSample = 0; // reset outputSample
    }
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
 envelope.trigger = 0;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
