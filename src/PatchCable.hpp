//
//  PatchCable.hpp
//  delay
//
//  Created by gustaf svenungsson on 13/03/2017.
//
//

#ifndef PatchCable_hpp
#define PatchCable_hpp

#include <stdio.h>
#include "ofMain.h"


class PatchClass;
class DrawObject;

class PatchCable{
    private :
    ofVec2f* startPos;
    ofVec2f* endPos;
    std::vector<const double*> connections;
    PatchClass* from;
    PatchClass* to;
    
    DrawObject* objFrom;
    DrawObject* objTo;
    
    vector<PatchClass*> myConnections;
    vector<DrawObject*> myDrawConnections;
public:
        PatchCable(ofVec2f& _startPos, ofVec2f& _mousePos, DrawObject& patchFrom, DrawObject& patchTo);
    
    
    ~PatchCable();
    void display();
    bool unpatch(const DrawObject& theObjectDeletingMe);
    void removeCoordinates();
};

#endif /* PatchCable_hpp */
