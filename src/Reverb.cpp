//
//  Reverb.cpp
//  delay
//
//  Created by gustaf svenungsson on 26/02/2017.
//
//

#include "Reverb.hpp"

//===============================================================================//

Reverb::Reverb(){
    output = 0;
    filters.clear();
    finalOutputIndex = 0;
    patchState = 0;
}

//===============================================================================//

void Reverb::addCombFilter(int _nums){
    for (int i = 0; i  < _nums; i++)
        filters.push_back(new CombFilter(44100, *this));
}

//===============================================================================//

void Reverb::addAllPassFilter(int _nums){
    for (int i = 0; i  < _nums; i++)
        filters.push_back(new AllPassFilter(44100, *this));
}

//===============================================================================//

void Reverb::setup(int index, float _time, float _rvt){
    int status = -4;
    
    char* realName;
    
    realName = abi::__cxa_demangle(typeid(*filters[index]).name(),0,0, &status);
    
    if(strcmp(realName, "CombFilter")==0)
        dynamic_cast<CombFilter*>(filters[index])->setGain(_time, _rvt);
    
    if(strcmp(realName, "AllPassFilter")==0)
        dynamic_cast<AllPassFilter*>(filters[index])->setGain(_time, _rvt);
}

//===============================================================================//


double Reverb::run(){
    for (const auto& obj : filters) obj->out();
    return output;
}

//===============================================================================//

void Reverb::out(){
    
}

//===============================================================================//

bool Reverb::sortByType(Filter* f1, Filter* f2){
    return f1->priority > f2->priority;
}

//===============================================================================//

void Reverb::removeFilterReference(const Filter& filterToDelete ){
    cout << "Remove Filter Reference Has Started"<< endl;
    
    filters.erase(std::remove_if(filters.begin(), filters.end(),
                           [&filterToDelete](Filter* i) { return i == &filterToDelete; }), filters.end());
    
    cout << "Remove Filter Reference Has Completed"<< endl;
}
