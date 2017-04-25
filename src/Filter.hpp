//
//  Filter.hpp
//  delay
//
//  Created by gustaf svenungsson on 21/02/2017.
//
//

#ifndef Filter_hpp
#define Filter_hpp

#include <stdio.h>
#include "ofxMaxim.h"
#include <numeric>
#include "PatchClass.hpp"

class Reverb;

//===============================================================================//

// we want all our delays to inherit everyhing from PatchClass plus a bunch more stuff

class Filter : public PatchClass {
    protected :
    vector<double> delayBuffer;
    int readIndex, writeIndex;
    Reverb* reverb;
    public :
    ~Filter();
    int startVal, maxVal, minVal;
   const int* delayTime;
    double delaySeconds;
    float millisInSampleRate;
    double ms(float _millis);
    Filter(int _sampleRate=44100);
    Filter(int _sampleRate, Reverb& _reverb);
    virtual void out();
    int samplerate;
    double milliseconds;
    void setup(int _ms);
    double sig;
    int priority;
    void runPatch();
};

//===============================================================================//

class Slapback : public Filter {
public:
    Slapback(int _sampleRate=44100);
    void out();
};

//===============================================================================//

class Echo : public Filter {
public:
    Echo(int _sampleRate=44100);
    void out();
    float decay;
    void setDecay(float _decay);
};

//===============================================================================//

class CombFilter : public Filter {
public:
    CombFilter(int _sampleRate=44100);
    CombFilter(int _sampleRate, Reverb& _reverb);
    void out();
    float gain, time, rvt;
    void setGain(float _time, float _rvt);
    ;
};

//===============================================================================//

class AllPassFilter : public Filter {
    public :
    void out();
    float gain, time, rvt;
    void setGain(float _time, float _rvt);
    AllPassFilter(int _sampleRate=44100);
    AllPassFilter(int _sampleRate, Reverb& _reverb);
};

//===============================================================================//


#endif /* Filter_hpp */
