//
//  OutPutManager.hpp
//  delay
//
//  Created by gustaf svenungsson on 18/03/2017.
//
//

#ifndef OutPutManager_hpp
#define OutPutManager_hpp

#include <stdio.h>
#include "FinalOutput.hpp"
#include "PatchClass.hpp"

// unfourtunately the current design requires each type of dsp object to be handled slightly differently so we need manager objects. These are responsible for the lifetime of a dsp object

class OutputManager{
private:
    vector<PatchClass*> connections; // keep track of all the connections
public:
    OutputManager();
    ~OutputManager();
    void out();
    void addNewOutputObject();
    void setOutput();
  //  void manageConnections(const FinalOutput* _connection);
    void removeOutputReference(const FinalOutput& audioSourceToDelete);
    vector<FinalOutput*> outputs;
    void run(double& _output);
    void printOutputs();
    double output;
};

#endif /* OutPutManager_hpp */
