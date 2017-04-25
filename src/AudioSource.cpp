//
//  AudioSource.cpp
//  delay
//
//  Created by gustaf svenungsson on 10/03/2017.
//
//

#include "AudioSource.hpp"
#include "InputManager.hpp"


AudioSource::~AudioSource(){
    cout << "Audio Source Destructor Started" << endl;
    inputManager->removeAudioSourceReference(*this);
    cout << "Audio Source Destructor Finished" << endl;
}

//===============================================================================//

AudioSource::AudioSource(int sampleRate, InputManager& _inputManager) :
PatchClass(sampleRate),
inputManager(&_inputManager)
{
    startVolume = 1;
    minVolume = 0;
    maxVolume = 1;
    parameters.emplace_back(new templateClass<double>(startVolume,minVolume,maxVolume,"input volume", setLevel));
}

//===============================================================================//

void AudioSource::out(){
    sumOfInputSignals();
    output =  inputSignal * (*setLevel);
}

//===============================================================================//

void AudioSource::runPatch(){
    out();
}

//===============================================================================//

