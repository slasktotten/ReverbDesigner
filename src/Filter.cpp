//
//  Filter.cpp
//  delay
//
//  Created by gustaf svenungsson on 21/02/2017.
//
//

#include "Filter.hpp"
#include "Reverb.hpp"

//===============================================================================//

/*
 delayCode modified from Simon Kataans A/V lectures
 
 combFilter and all-pass filter modified from The Audio Programming Book by Richard Boulanger and Victor Lazzarini
 */
Filter::Filter(int _sampleRate, Reverb& _reverb) :
samplerate(_sampleRate),
reverb(&_reverb)
{
    readIndex  = 0;
    writeIndex = 0;
    millisInSampleRate = _sampleRate/1000; // one milliseconds worth with current sampleRate
    delayBuffer.resize(_sampleRate);
}

double Filter::ms(float _millis)
{
    return millisInSampleRate * _millis; // return milliseconds
}

void Filter::setup(int _ms)
{
    milliseconds = (int)ms(_ms); //
}

void Filter::out()
{

}

void Filter::runPatch()
{
    
}

Filter::~Filter(){
    cout <<"filter destructor called" << endl;
    reverb->removeFilterReference(*this); // when we delete a filter object we need to remove its reference from its manager object, in this case the Reverb
    cout <<"filter destructor has finished" << endl;
}

//===============================================================================//

Slapback::Slapback(int _sampleRate) : Filter(_sampleRate){}

void Slapback::out(){
    sumOfInputSignals();
    readIndex = writeIndex - milliseconds;
    if(readIndex < 0) readIndex += delayBuffer.size();
    delayBuffer[writeIndex] = inputSignal;
    writeIndex = ++writeIndex % delayBuffer.size();
    output = inputSignal + delayBuffer[readIndex];
    inputSignal = 0;
}


//===============================================================================//

Echo::Echo(int _sampleRate) : Filter(_sampleRate){
    decay = 0.3;
}

void Echo::setDecay(float _decay){
    if (_decay > 1) cout << "FEEDBACK WARNING" << endl;
    decay = _decay;
}

void Echo::out(){
    sumOfInputSignals();
    readIndex = writeIndex - milliseconds;
    if(readIndex < 0) readIndex += delayBuffer.size();
    delayBuffer[writeIndex] = inputSignal + delayBuffer[readIndex] * decay;
    writeIndex = ++writeIndex % delayBuffer.size();
    output = inputSignal + delayBuffer[readIndex];
    inputSignal = 0;
}

//===============================================================================//



CombFilter::CombFilter(int _sampleRate, Reverb &_reverb) :
Filter(_sampleRate, _reverb){
    maxVal = delayBuffer.size();
    minVal = 1;
    startVal = 500;
    time = (int)ms(1.7);
    rvt  = (int)ms(32.92);
    gain = pow(0.001,(time/rvt));
    priority = 0;
    parameters.emplace_back(new templateClass<int>(startVal, minVal, maxVal, "delay time", delayTime));
}


void CombFilter::setGain(float _time, float _rvt){
    time = (int)ms(_time);
    rvt  = (int)ms(_rvt);
    gain = pow(0.001,(time/rvt));
}

void CombFilter::out(){
    sumOfInputSignals();
    readIndex = writeIndex - (*delayTime); // output - delayTime ago
    if(readIndex < 0) readIndex += delayBuffer.size(); // if less than zero, output from end of vector
    delayBuffer[writeIndex] = inputSignal + delayBuffer[readIndex] * gain;  // multiply feedback with appropriate gain
    writeIndex = ++writeIndex % delayBuffer.size(); // need to make sure the writeIndex loops around to the start when we've reached the end
    output = inputSignal + delayBuffer[readIndex]; // output original signal plus the delayed
}

//===============================================================================//



AllPassFilter::AllPassFilter(int _sampleRate, Reverb& _reverb) :
Filter(_sampleRate, _reverb)
{
    samplerate = _sampleRate;
    maxVal = delayBuffer.size();
    minVal = 1;
    startVal = 500;
    time = (int)ms(1.7);
    rvt = (int)ms(70.5);
    gain = pow(0.001, (time/rvt)); // gain needs to be a function that dereferences the pointers
    priority = 1;
    parameters.emplace_back(new templateClass<int>(startVal, minVal, maxVal, "delay time", delayTime));
    
}

void AllPassFilter::out(){
    sumOfInputSignals();
    readIndex = writeIndex - (*delayTime);
    if(readIndex < 0) readIndex += delayBuffer.size();
    delayBuffer[writeIndex] = inputSignal + delayBuffer[readIndex] * gain;
    writeIndex = ++writeIndex % delayBuffer.size();
    output = delayBuffer[readIndex] - inputSignal * gain; // take away inputSignal * gain for more even frequency response
}

void AllPassFilter::setGain(float _time, float _rvt){
    time = (int)ms(_time);
    rvt  = (int)ms(_rvt);
    gain = pow(0.001,(time/rvt));
}
