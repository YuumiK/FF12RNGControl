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
    int lv = 66;
    int magic = 99;
    double result = 20 + (RNG % (int)(20 * 12.5)) / 100.0;
    return (int)(result * (magic * (magic + lv)/256.0 + 2.0) * 1.5);
}
bool treasure(unsigned long RNG)
{
    return (RNG % 100 < 6);
}

int main(int argc, const char * argv[]) {
    MT mt;
    
    std::vector<int> curelist;
    curelist.push_back(2047);
    curelist.push_back(2126);
    curelist.push_back(2192);
    
    std::cout << (mt.determinePosition(cure, curelist, 1) ? "found" : "not found") << std::endl;
    //mt.search(treasure, 1000);
    
    return 0;
}
