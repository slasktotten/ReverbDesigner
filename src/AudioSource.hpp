//
//  AudioSource.hpp
//  delay
//
//  Created by gustaf svenungsson on 10/03/2017.
//
//

#ifndef AudioSource_hpp
#define AudioSource_hpp

#include <stdio.h>
#include "PatchClass.hpp"
#include <ofMain.h>

class InputManager;

class AudioSource : public PatchClass
{
private:
    void out();
    const  double* setLevel;
    std::vector<const double*> audioSources;
    InputManager* inputManager;
    templateClass<double>* param;
    double startVolume, minVolume, maxVolume;
    
public:
    
    AudioSource(int sampleRate, InputManager& _inputManager);
    ~AudioSource();
    void addAudioSource(const double& newInputSource);
    int hasAPatch;
    void run();
    void setInput(const double& newInputSource);
    void runPatch();
};

#endif /* AudioSource_hpp */
