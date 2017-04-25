//
//  Patch.hpp
//  delay
//
//  Created by gustaf svenungsson on 27/02/2017.
//
//

#ifndef Patch_hpp
#define Patch_hpp

#include <stdio.h>

class Patch {
    public :
    Patch();
    double parallel();
    double serial();
    int sum;
};

#endif /* Patch_hpp */
