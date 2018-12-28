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
    else if(n < 0 && getCurrentPosition() > 0)
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

unsigned int RNG_base::search(std::function<bool(unsigned long)> f, unsigned long timeoutMillsec)
{
    time_t startTime = time(nullptr);
    unsigned int prevPosition = getCurrentPosition();
    while(time(nullptr) - startTime < timeoutMillsec){
        forward();
        if(f(getCurrentRN()))//found
        {
            unsigned int foundPosition = getCurrentPosition();
            shiftRNG(foundPosition - prevPosition);
            return foundPosition;
        }
    }
    return 0;
}

bool RNG_base::determinePosition(std::function<int(unsigned long)> f, std::vector<int> curelist, unsigned long timeoutMillsec)
{
    time_t startTime = time(nullptr);
    
    assert(curelist.size() > 0);
    //unsigned long prevPosition = getCurrentPosition();
    while(time(nullptr) - startTime < timeoutMillsec)
    {
        forward();
        if (f(getCurrentRN()) == curelist[0])
        {
            std::cout << "debug:curelist[0] found in " << getCurrentPosition() << ":" << getCurrentRN() << std::endl;
            for (int i = 1; i < curelist.size(); i++)
            {
                forward();
                if (f(getCurrentRN()) == curelist[i])
                {
                    std::cout << "debug:curelist["<< i <<"] found in " << getCurrentPosition() << ":" << getCurrentRN() << std::endl;
                     if(i == curelist.size() - 1) return true;
                }
                else
                {
                    for (int j = 0; j < i; j++)
                    {
                        backward();
                    }
                    break;
                }
            }
        }
    }
    return false;
}


std::vector<unsigned long> RNG_base::getRNGlist(int count)//start current end current +(count - 1)
{
    std::vector<unsigned long> result;
    for(int i = 0; i < count; i++)
    {
        result.push_back(getCurrentRN());
        forward();
    }
    for(int i = 0; i < count; i++) backward();
    
    return result;
}
