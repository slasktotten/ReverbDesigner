//
//  PatchCable.cpp
//  delay
//
//  Created by gustaf svenungsson on 13/03/2017.
//
//

#include "PatchCable.hpp"
#include "PatchClass.hpp"
#include "DrawObject.hpp"

PatchCable::PatchCable(ofVec2f& _startPos, ofVec2f& _mousePos, DrawObject& patchFrom, DrawObject& patchTo) :
startPos(&_startPos),
endPos(&_mousePos),
objFrom(&patchFrom),
objTo(&patchTo)
{

}

PatchCable::~PatchCable(){
    cout << "patch cable destructor called" << endl;
    to = nullptr;
    from = nullptr;
    objTo = nullptr;
    objFrom = nullptr;
    startPos = nullptr;
    endPos = nullptr;
    startPos = nullptr;
    endPos = nullptr;
    cout << "patch cable destructor has finished" << endl;
}


void PatchCable::display (){
    ofSetColor(250);
    ofSetLineWidth(5);
    ofFill();
    ofDrawLine(*startPos, *endPos);
}

void PatchCable::removeCoordinates(){
    startPos = nullptr;
    endPos = nullptr;
    
}

// there's a reference to the patchCable in both the to and from object, so check which one is deleting it
bool PatchCable::unpatch(const DrawObject& theObjectDeletingMe){
    if(&theObjectDeletingMe == objFrom || &theObjectDeletingMe == objTo){
        return true;
    }
    return false;
}


