//
//  OutPutManager.cpp
//  delay
//
//  Created by gustaf svenungsson on 18/03/2017.
//
//

#include "OutPutManager.hpp"

OutputManager::OutputManager()
{
    
    connections.clear();
    
}

//===============================================================================//

OutputManager::~OutputManager()
{
    
}

//===============================================================================//

void OutputManager::addNewOutputObject(){
    
    outputs.push_back(new FinalOutput(4410, *this));
    
}

//===============================================================================//

void OutputManager::run(double& _output){
    
    for (auto& el : outputs) el->out(_output);
    
}

//===============================================================================//

void OutputManager::printOutputs(){
    
    for (auto& el : outputs) cout << el << endl;

}

//===============================================================================//

// when we delete a finalOutput object we need to make sure the reference to it is deleted from the manager object
// also remove the element from the output managers vector
void OutputManager::removeOutputReference(const FinalOutput& outputToDelete){
    // iterate over the vector to find the object we want to delete
    outputs.erase(std::remove_if(outputs.begin(), outputs.end(),
                                 [&outputToDelete](FinalOutput* i) { return i == &outputToDelete; }), outputs.end());
}
