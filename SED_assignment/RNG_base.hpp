//
//  RNG_base.hpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/26.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#ifndef RNG_base_hpp
#define RNG_base_hpp

#include <iostream>
#include <cassert>
#include <ctime>
#include <vector>

class RNG_base{
   
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
    
    //search
    unsigned int search(std::function<bool(unsigned long)> f, unsigned long timeoutMillsec);
    bool determinePosition(std::function<int(unsigned long)> f, std::vector<int> curelist, unsigned long timeoutMillsec);
    
    //for cui output
    std::vector<unsigned long> getRNGlist(int count);
};

#endif /* RNG_base_hpp */
