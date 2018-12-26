//
//  RNG_base.hpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/26.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#ifndef RNG_base_hpp
#define RNG_base_hpp

#include <stdio.h>
#include <cassert>

class RNG_base{
   
private:
    
protected:
    unsigned int currentPosition;
    unsigned long currentRN;
    virtual void forward();
    virtual void backward();
    virtual void initializeAlgorithm();
    
public:
    RNG_base();
    ~RNG_base();
    void shiftRNG(int n);
    unsigned int getCurrentPosition();
    unsigned long getCurrentRN();
};

#endif /* RNG_base_hpp */
