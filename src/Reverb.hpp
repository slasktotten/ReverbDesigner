//
//  Reverb.hpp
//  delay
//
//  Created by gustaf svenungsson on 26/02/2017.
//
//

#ifndef Reverb_hpp
#define Reverb_hpp

#include <stdio.h>
#include "Filter.hpp"
#include <typeinfo>
#include <cxxabi.h>
#include <map>

class Reverb
{
private:
    public :
    Reverb();
    double output;
    void addCombFilter(int _nums);
    void addAllPassFilter(int _nums);
    vector<Filter*> filters;
    void out();
    void setup(int index, float _time, float _rvt);
    double run();
    double outputSignal();
    int finalOutputIndex;
    static bool sortByType(Filter* filter, Filter* filter2);
    int patchState;
    void removeFilterReference(const Filter& filterToDelete);
    
    
};

#endif /* Reverb_hpp */
