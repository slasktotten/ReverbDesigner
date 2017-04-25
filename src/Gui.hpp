//
//  Gui.hpp
//  delay
//
//  Created by gustaf svenungsson on 05/03/2017.
//
//

#ifndef Gui_hpp
#define Gui_hpp

#include <stdio.h>
#include <ofMain.h>
#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofxGui.h"
#include "Reverb.hpp"
#include "DrawObject.hpp"
#include "ofEvents.h"
#include "PatchClass.hpp"
#include "PatchCable.hpp"
#include "InputManager.hpp"
#include "OutputManager.hpp"


class Gui{
private:
    bool deleteState;
    list<PatchCable*> cables; // list instead of vector so that when we delete items our pointers dont become invalid
    ofVec2f* pStart; // start and end pos of patchCables
    ofVec2f* pEnd;
    Reverb* reverb;
    InputManager* inputManager;
    OutputManager* outputManager;
    PatchClass* patchFrom;
    PatchClass* patchTo;
    DrawObject* objFrom;
    DrawObject* objTo;
    
    // methods
    void addComb();
    void addAllPass();
    void addAudioSourceObject();
    void addFinalOutput();
    void addOutput();
    
    void toggleDeletState();
    void resetPatching(string returnMsg);
    bool result;
    void createObject(int x, int y);
    void deleteObject(int x, int y);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void patchStatus(bool mouseBool);
    bool anyElementFalse(DrawObject& _drawObject);
    list<DrawObject*> drawObject;
    
    // mouse events
    void mPressed(ofMouseEventArgs & args);
    void mDragged(ofMouseEventArgs & args);
    void mReleased(ofMouseEventArgs & args);
    
    // parameters
    ofParameterGroup parametergroup;
    ofParameter<float> rvt;
    ofParameter<float> time;
    ofParameter<double> te;
    
    vector<ofParameter<double>*> dblPara;
    vector<ofParameter<int>*> intPara;
    vector<ofParameter<float>*> floatPara;
    
    // buttons
    ofxButton createCombFilter;
    ofxButton createAllPassFilter;
    ofxButton createOutput;
    ofxButton createAudioSource;
    ofxButton createFinalOutput;
    
    ofxButton deleteCombFilter;
    ofxButton deleteAnObject;
    ofxButton deleteAllPassFilter;
    
    // colors
    ofColor combFilterHighlight;
    ofColor combFilterIdle;
    ofColor allPassHighlight;
    ofColor allPassIdle;
    ofColor audioSourceHiglight;
    ofColor audioSourceIdle;
    
    // gui panel
    ofxPanel gui;
    
    void setGUI(string name);
    void setNewParameterGroup(PatchClass& patch, string guiName);
    
    
public:
    Gui(Reverb& _patch, InputManager& _inputManager, OutputManager& _outputManager);
    ~Gui();
    void setup(string name);
    void draw();
    void resetParameters();
    void update(int x, int y);
    
    

};

#endif /* Gui_hpp */
