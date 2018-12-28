//
//  OutputComponent.hpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/28.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#ifndef OutputComponent_hpp
#define OutputComponent_hpp

#include <iostream>
#include <iomanip>
#include "RNG_base.hpp"


using namespace std;
class OutputComponent{
public:
    void printMessage(const string message);
    int getIntegerText(const string message, int max, int min);
    bool getYNText(const string message);
    void printRNTable(int count, RNG_base &rngbase);
};

#endif /* OutputComponent_hpp */
