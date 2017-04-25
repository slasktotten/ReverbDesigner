//
//  InputManager.cpp
//  delay
//
//  Created by gustaf svenungsson on 18/03/2017.
//
//

#include "InputManager.hpp"
/*
pretty much identical to outputManager
 please see majority of commenting there.
 where the code differs i've commented
 */


InputManager::InputManager()
{
    audioInputs.clear();
}

//===============================================================================//

InputManager::~InputManager()
{
    
}

//===============================================================================//

void InputManager::removeAudioSourceReference(const AudioSource& audioSourceToDelete){
        sources.erase(std::remove_if(sources.begin(), sources.end(),
        [&audioSourceToDelete](AudioSource* i) { return i == &audioSourceToDelete; }), sources.end());
}

//===============================================================================//

// inputManager is respnsible for managing all of the possible inputs
void InputManager::addNewInput(const double& _input){
    audioInputs.push_back(&_input);
}

//===============================================================================//

void InputManager::addAudioSourceObject(){
    sources.push_back(new AudioSource(44100, *this));
    setInput();
}

//===============================================================================//
// but here we actually set which input our audioSource objects are going to have
void InputManager::setInput(){
    for (auto& source : sources) source->patch(*audioInputs[0]);
}

//=====================================================================
//===============================================================================//

void InputManager::run(){
    for (const auto& source : sources) source->runPatch();
}

//===============================================================================//

void InputManager::printSources(){
    for (const auto& el : sources)
        cout << el << endl;
}
