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
private:
    unsigned int currentPosition;
    unsigned long currentRN;
protected:
    virtual void forward();
    virtual void backward();
    virtual void initializeAlgorithm();
    void add1CurrentPosition();
    void sub1CurrentPosition();
    void setCurrentRN(unsigned long rn);
    
public:
    RNG_base();
    ~RNG_base();
    void shiftRNG(int n);
    unsigned int getCurrentPosition();
    unsigned long getCurrentRN();
    
    //search
    unsigned int search(std::function<bool(std::vector<unsigned long>)> f,int numOfRequireRNs, unsigned long timeoutMillsec);
    // return how many positions are found in given curelist. if it's 1, then position will be shifted to that position. else position are reset to initial position.
    int determinePosition(std::function<int(unsigned long)> f, std::vector<int> curelist, unsigned long timeoutMillsec);
    
    //getRNGlist from currentPosition to currentPosition + count - 1
    std::vector<unsigned long> getRNGlist(int count);
};

#endif /* RNG_base_hpp */
