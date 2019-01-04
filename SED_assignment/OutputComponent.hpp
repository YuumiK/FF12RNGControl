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
    static void printRNTable(RNG_base &rngbase, int count = 10);
    //static void printRNTablewithCure(RNG_base &rngbase, std::function<int(unsigned long)> f, int count);
    //static void printRNTablewithEvent(RNG_base &rngbase, std::function<bool(std::vector<unsigned long>)> f, int count);
};

#endif /* OutputComponent_hpp */
