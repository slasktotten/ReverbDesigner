//
//  DrawObject.cpp
//  delay
//
//  Created by gustaf svenungsson on 06/03/2017.
//
//

#include "DrawObject.hpp"


/*
 most of collision code adapted from processings
 https://processing.org/examples/mousefunctions.html
 
 */

DrawObject::DrawObject(PatchClass& _patch,  ofColor col1, ofColor col2, int w, int h) :
patch(&_patch),
width(w),
heigth(h)

{
    posX = ofGetWidth()/2;
    posY = ofGetHeight()/2;
    size = 75;
    overBox = false;
    locked  = true;
    ofSetRectMode(OF_RECTMODE_CENTER);
    highLightColor = col1;
    idleColor = col2;
}

DrawObject::~DrawObject(){
    cout << "draw object destructor called" << endl;
    // when we delete a drawObject we need to delete all of its patchCable connections
    for(auto& cable : cableConnections){
        cable->removeCoordinates();
        cable = nullptr;
        delete cable;
    }
    // we then want to delete the patch (dsp object)
    delete patch;
    patch = nullptr;
    cout << "draw object destructor has finished" << endl;
}

void DrawObject::mPressed(int x, int y)
{
    // if we are over a drawObject when mouse is pressed, set selected and locked to true
    // otherwise set them to false
    if(overBox) {
        selected = true;
        locked   = true;
        } else {
        locked = false;
        selected = false;
    }
    xOffset = x-posX;
    yOffset = y-posY;
}

// code for dragging a drawObject around the screen
void DrawObject::mDragged(int x, int y)
{
    // add an offset so its easier to get a hold of the drawObject
    if(locked) {
        posX = x-xOffset;
        posY = y-yOffset;
    }
}

void DrawObject::mReleased(int x, int y)
{
    locked = false;
}

// collision detection
void DrawObject::collision(int x, int y){
    if (x > posX-size && x  < posX+size &&
        y  > posY-size && y < posY+size) {
        overBox = true;
        if(!locked) {
            ofFill();
        }
    } else {
        ofFill();
        overBox = false;
    }
}

void DrawObject::display()
{
    ofSetColor(idleColor);
    getMyPos.x = posX;
    getMyPos.y = posY;
    ofDrawRectangle(posX, posY, size, size);
}

// each drawObject needs to know about all it's connections
void DrawObject::addCableReference(PatchCable& cable){
    cableConnections.push_back(&cable);
}

// each drawObject stores a pointer to a patchClass object
// this what you retrive when you click on a drawObject
PatchClass* DrawObject::getMyPtr(){
    cout << "pointer returned is of type: " << typeid(*patch).name() <<  endl;
    return patch;
}
