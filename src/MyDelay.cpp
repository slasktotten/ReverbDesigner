//
//  MyDelay.cpp
//  delay
//
//  Created by gustaf svenungsson on 13/02/2017.
//
//

#include "MyDelay.hpp"

MyDelay::MyDelay(){
    readIndex  = 0;
    writeIndex = 0;
    delaySeconds = 0.05; //this parameter needs to be set in the constructor
    decay = 0.5;
    delayBuffer.resize(88200);
    //desired reverb time in ms
    time = (int)ms(1.7);
    rvt = (int)ms(32.92);
    gain = pow(0.001, (time/rvt));
}


// based of delayline code provided by Simon Katan in Audio Visual Programming
double MyDelay::sb(double signal){
    readIndex = writeIndex - int(delaySeconds * 44100);
    if(readIndex < 0) readIndex += delayBuffer.size();
    delayBuffer[writeIndex] = signal;
    writeIndex = ++writeIndex % delayBuffer.size();
    return signal + delayBuffer[readIndex];
}


double MyDelay::combfilter(double signal){
    readIndex = writeIndex - (int)ms(29.7);
    if(readIndex < 0) readIndex += delayBuffer.size();
    delayBuffer[writeIndex] = signal + delayBuffer[readIndex] * gain;
    writeIndex = ++writeIndex % delayBuffer.size();
    return signal + delayBuffer[readIndex];
}

double MyDelay::allPassFilter(double signal){
    readIndex = writeIndex - (int)ms(29.7);
    if(readIndex < 0) readIndex += delayBuffer.size();
    delayBuffer[writeIndex] = signal + delayBuffer[readIndex] * gain;
    writeIndex = ++writeIndex % delayBuffer.size();
    return delayBuffer[readIndex] - signal * gain;
}

double MyDelay::echo(double signal){
    readIndex = writeIndex - int(delaySeconds * 44100);
    if(readIndex < 0) readIndex += delayBuffer.size();
    delayBuffer[writeIndex] = signal + delayBuffer[readIndex] * decay;
    writeIndex = ++writeIndex % delayBuffer.size();
    return  delayBuffer[readIndex] - signal*gain;
}

double MyDelay::ms(float _millis){
    float msec = 44100/1000;
    return msec * _millis;
    
}
