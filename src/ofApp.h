#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "Filter.hpp"
#include "Reverb.hpp"
#include "Gui.hpp"
#include "AudioSource.hpp"
#include "InputManager.hpp"
#include "FinalOutput.hpp"
#include "OutputManager.hpp"
#define sampleRate 44100



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    maxiOsc osc;
    maxiEnv envelope;
    maxiSample beat;
    maxiMix mix;
    Reverb* reverb;
    AudioSource* audioSourceManager;
    Gui* gui;
    InputManager* inputManager;
    OutputManager* outputManager;
    
    bool check;

    const int buffersize = 512;
    int frequency;
    double outputs[2];
        
    double currentsample, volume, currentframe;
    void audioOut(float * output, int bufferSize, int nChannels);
    
    double outputSample;
    
  


};
