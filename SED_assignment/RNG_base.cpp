//
//  RNG_base.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/26.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "RNG_base.hpp"


RNG_base::RNG_base()
{
    currentPosition = 0;
    currentRN = 0;
    initializeAlgorithm();
}
RNG_base::~RNG_base()
{
}

void RNG_base::forward()
{
    
}
void RNG_base::backward()
{
    
}
void RNG_base::initializeAlgorithm()
{
    
}

void RNG_base::shiftRNG(int n)
{
    if(n > 0)
    {
        forward();
        shiftRNG(n-1);
    }
    else if(n < 0)
    {
        backward();
        shiftRNG(n+1);
    }
    return;
}

unsigned int RNG_base::getCurrentPosition()
{
    return currentPosition;
}

unsigned long RNG_base::getCurrentRN()
{
    return currentRN;
}
