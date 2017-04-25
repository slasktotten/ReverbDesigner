//
//  InputManager.hpp
//  delay
//
//  Created by gustaf svenungsson on 18/03/2017.
//
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include <stdio.h>
#include "AudioSource.hpp"
#include "PatchClass.hpp"


class InputManager{
private:
    vector<PatchClass*> connections;
    vector<const double*> audioInputs;
    
public:
    InputManager();
    ~InputManager();
    void out();
    void addNewInput(const double& _input);
    void addAudioSourceObject();
    void setInput();
    void runAudioSource(PatchClass& args);
    void removeAudioSourceReference(const AudioSource& audioSourceToDelete);
       vector<AudioSource*> sources;
    void run();
    void printSources();
};

#endif /* InputManager_hpp */
