//
//  DrawObject.hpp
//  delay
//
//  Created by gustaf svenungsson on 06/03/2017.
//
//

#ifndef DrawObject_hpp
#define DrawObject_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Filter.hpp"
#include "ofEvents.h"
#include "PatchCable.hpp"



class DrawObject{
    private :
    int
    xOffset,
    yOffset,
    size,
    width,
    heigth;
    int posX, posY;
    PatchClass* patch; // each drawObject is responsible for a patchClass object
    ofColor highLightColor;
    vector<PatchCable*> cableConnections;
    void deleteCableReferences();
    
public:
    DrawObject(PatchClass& _patch, ofColor col1, ofColor col2, int w = 50, int h = 20 );
    ~DrawObject();
    void display();
    void mPressed(int x, int y);
    void mDragged(int x, int y);
    void mReleased(int x, int y);
    void mMoved(int x, int y);
    void collision(int x, int y);
    bool overBox;
    bool locked;
    bool selected;
    void addCableReference(PatchCable& cable);
 
    PatchClass* getMyPtr();
    ofColor idleColor;
    ofVec2f getMyPos;
   
   // const double* audioSource;
};


#endif /* DrawObject_hpp */
