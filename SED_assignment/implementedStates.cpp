//
//  implementedStates.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "implementedStates.hpp"


//Calibration
void Calibration::execute(RNG_base &rng, OutputComponent &output)
{
    output.printMessage("Calibration execute");
    
}
void Calibration::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}

//Mainmenu
Mainmenu::Mainmenu()
{
    next = 0;
}
void Mainmenu::execute(RNG_base &rng, OutputComponent &output)
{
    output.printMessage("Mainmenu execute");
    next++;
}

void Mainmenu::nextState(Context *context)
{
    if(next == 10) context -> Exit();
    context->changeState(Determine::getInstance());
}

//Determine
void Determine::execute(RNG_base &rng, OutputComponent &output)
{
    output.printMessage("Determine execute");
}
void Determine::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}

//Adjustment
void Adjustment::execute(RNG_base &rng, OutputComponent &output)
{
    int n = output.getIntegerText("enter the amount of shift",INT_MAX, INT_MIN);
    rng.shiftRNG(n);
    int displayRNnum = 10;
    output.printRNTable(displayRNnum, rng);
}
void Adjustment::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}

//Configure
void Configure::execute(RNG_base &rng, OutputComponent &output)
{
    output.printMessage("Configure execute");
}
void Configure::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}
