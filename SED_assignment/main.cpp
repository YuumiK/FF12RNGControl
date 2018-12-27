//
//  main.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/26.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "MT.hpp"
#include <iostream>
int cure(unsigned long RNG)
{
    int lv = 99;
    int magic = 99;
    return (RNG%250) * (magic * (magic + lv)/256 + 2) /100 * 1;
}
bool treasure(unsigned long RNG)
{
    return (RNG % 100 < 6);
}

int main(int argc, const char * argv[]) {
    MT mt;
    mt.shiftRNG(7000);
    
    std::vector<int> curelist;
    curelist.push_back(2589);
    curelist.push_back(2436);
    curelist.push_back(2629);
    
    std::cout << (mt.determinePosition(cure, curelist, 1000) ? "found" : "not found") << std::endl;
    //mt.search(treasure, 1000);
    
    return 0;
}
