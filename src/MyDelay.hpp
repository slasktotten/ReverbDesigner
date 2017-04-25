//
//  MyDelay.hpp
//  delay
//
//  Created by gustaf svenungsson on 13/02/2017.
//
//

#ifndef MyDelay_hpp
#define MyDelay_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxMaxim.h"
#include <math.h>

// abstract base class



class MyDelay {
public:
    vector<double> delayBuffer;
    double delaySeconds;
    double sb(double signal);
    double echo(double signal);
    double combfilter(double signal);
    double allPassFilter(double signal);    
    int readIndex, writeIndex;
    float decay;
    float gain;
    double rvt;
    double time;
    double ms(float _millis);
    MyDelay();
};



#endif /* MyDelay_hpp */
