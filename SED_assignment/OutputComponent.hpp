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
#include <cctype>
#include <algorithm>
#include "RNG_base.hpp"
#include "nextState.hpp"
#include "Context.hpp"

//using namespace std;
struct OutputComponent{
    void printMessage(const std::string message);
    int getIntegerText(const std::string message, int max, int min);
    PARAMETERS getParam(const std::string message);
    NEXT_STATE getNextState(const std::string message);
    bool getYNText(const std::string message);
    void printRNTable(int count, RNG_base &rngbase);
};

#endif /* OutputComponent_hpp */
