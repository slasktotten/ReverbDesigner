//
//  FinalOutput.cpp
//  delay
//
//  Created by gustaf svenungsson on 11/03/2017.
//
//

#include "FinalOutput.hpp"
#include "OutputManager.hpp"



FinalOutput::FinalOutput(int sampleRate, OutputManager& _outputManager) :
PatchClass(sampleRate),
outputManager(&_outputManager)
{
    startVolume = 1;
    minVolume = 0;
    maxVolume = 1;
    parameters.emplace_back(new templateClass<double>(startVolume, minVolume, maxVolume, "output volume", outputVolume));

}

//===============================================================================//

FinalOutput::~FinalOutput(){
    cout << "Finaloutput destructor started" << endl;
    outputManager->removeOutputReference(*this);
    cout << "Finaloutput destructor finished" << endl;
}

//===============================================================================//

void FinalOutput::out()
{

}

//===============================================================================//

// we input the final outputsample in audioThread here so that we can change its value to the input of our finalOutput Obkect
void FinalOutput::out(double& outputSample){
    sumOfInputSignals();
    outputSample  += (inputSignal) * (*outputVolume);
   }

//===============================================================================//

void FinalOutput::runPatch()
{
    
}
