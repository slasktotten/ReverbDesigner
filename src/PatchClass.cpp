//
//  PatchClass.cpp
//  delay
//
//  Created by gustaf svenungsson on 09/03/2017.
//
//

#include "PatchClass.hpp"

PatchClass::PatchClass(int argsSampleRate)
{
    
}

//===============================================================================//
// when we delete a patchClass object we need to find all the other patchClass objects that has reference to it and delete that reference
PatchClass::~PatchClass(){
    
    std::cout << "patchclass destructor called" << std::endl;
    
    for (auto& el : patchObjConnections) el->deleteInputSignal(output, *this);
    
    cout << "patchclass destructor has finished"  << endl;
    
}

//===============================================================================//
// patch a new input signal - i.e. add a reference to a PatchClass objects output variable
void PatchClass::patch(const double& input){
    inputs.push_back(&input);
}

//===============================================================================//

// grab a patchClass object and get the .output variable
void PatchClass::patch(const PatchClass &patchFrom, PatchClass &patchTo)
{
    
    patchTo.patch(patchFrom.output);
    
}

//===============================================================================//

// directly get a reference to an output variable
void PatchClass::patch(const double& patchFrom, PatchClass& patchTo)
{
    
    patchTo.patch(patchFrom);
    
}

//===============================================================================//

void PatchClass::sumOfInputSignals(){
    // sum up all the input signals
    // we use a lambda because its fast and allows to accumulate to easily dereference and add together values the pointers are pointing to
    inputSignal =
    std::accumulate(inputs.begin(), inputs.end(), 0.0, [] (const double var, const double* p)
    {  return var + *p; });

}

//===============================================================================//

// only for reading
double PatchClass::getSumOfInputSignals() const{
    
    return inputSignal;

}

//===============================================================================//


// each patchClass object needs to know what it is connected to, so add references to the cable connections and patchObjects
void PatchClass::addConnection(PatchCable& addCableConnection, PatchClass& addPatchObjConnection){
    
    cableConnection.push_back(&addCableConnection);
    
    patchObjConnections.emplace_back(&addPatchObjConnection);
    
}

//===============================================================================//

// delete reference to a patchClass object, this is called from another patchClass
void PatchClass::deleteInputSignal(const double& theInputToBeDeleted, const PatchClass& patchObjToDelete){
    // find the the inputSignal we need to delete, and delete the reference to that object
    std::vector<const double*>::iterator inputIterator;
    
    inputs.erase(std::remove(inputs.begin(), inputs.end(), &theInputToBeDeleted), inputs.end());
    
    std::vector<const PatchClass*>::iterator patchObjIterator;
    
        patchObjConnections.erase(std::remove(patchObjConnections.begin(), patchObjConnections.end(), &patchObjToDelete), patchObjConnections.end());
    
}

//===============================================================================//

void PatchClass::runPatch()
{
    
}


//===============================================================================//
