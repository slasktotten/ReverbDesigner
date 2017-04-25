//
//  FinalOutput.hpp
//  delay
//
//  Created by gustaf svenungsson on 11/03/2017.
//
//

#ifndef FinalOutput_hpp
#define FinalOutput_hpp

#include <stdio.h>
#include "PatchClass.hpp"

class OutputManager;

class FinalOutput : public PatchClass{
private:
    void out();
    const double* outputVolume;
    public:
    void out (double& outputSample);
    FinalOutput(int sampleRate, OutputManager& _outputManager);
    ~FinalOutput();
    void runPatch();
    OutputManager* outputManager;
    double* setLevel;
    double startVolume, minVolume, maxVolume;
};


#endif /* FinalOutput_hpp */
