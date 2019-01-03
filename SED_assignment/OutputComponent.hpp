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
#include "Context.hpp"

enum PARAMETERS : int;

//using namespace std;
struct OutputComponent{
    static void printMessage(const std::string message);
    static int getIntegerText(const std::string message, int max, int min);
    static float getFloatText(const std::string message, float max, float min);
    static void printParameters();
    static PARAMETERS getParam(const std::string message);
	static bool getYNText(const std::string message);
    static void printRNTable(int count, RNG_base &rngbase);
};

#endif /* OutputComponent_hpp */
