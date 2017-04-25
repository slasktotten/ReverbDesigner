//
//  PatchClass.hpp
//  delay
//
//  Created by gustaf svenungsson on 09/03/2017.
//
//

#ifndef PatchClass_hpp
#define PatchClass_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include "PatchCable.hpp"
#include "TemplatedParameter.h"


class PatchClass
{
protected:
    virtual void sumOfInputSignals();
    virtual void out() = 0;
    double inputSignal;
    std::vector<const double*> inputs;
    std::vector<PatchCable*> cableConnection;
    std::vector<PatchClass*> patchObjConnections;
    void setParameters(const int& par);
    void setParameters(const float& par);
    
public:
PatchClass(int argsSampleRate = 44100);
 virtual ~PatchClass() = 0;
    virtual void patch(const double& input);
    virtual void patch(const PatchClass& patchFrom, PatchClass& patchTo);
    virtual  void patch(const double& patchFrom, PatchClass& patchTo);
    double output;
    double getSumOfInputSignals() const;
    void deleteInputSignal(const double& _theInputToBeDeleted, const PatchClass& patchObjToDelete);
    void addConnection(PatchCable& addCableConnection, PatchClass& addPatchObjConnection);
    void deleteCableConnection(PatchCable& cableToDelete);
    virtual void runPatch();
    vector<templateInterface*> parameters;

};

#endif /* PatchClass_hpp */
