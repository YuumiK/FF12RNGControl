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
    next = NEXT_STATE::CALIBRATION;
}
void Mainmenu::execute(RNG_base &rng, OutputComponent &output)
{
    output.printMessage("Mainmenu 1:Calibration,2:Determination,3:Adjustment,4:Config,0:Exit");
    next = output.getNextState("Next command");
}

void Mainmenu::nextState(Context *context)
{
    switch (next){
        case NEXT_STATE::CALIBRATION:
     		context->changeState(Calibration::getInstance());
            break;
        case NEXT_STATE::DETERMINATION:
            context->changeState(Determine::getInstance());
            break;
        case NEXT_STATE::ADJUSTMENT:
            context->changeState(Adjustment::getInstance());
            break;
        case NEXT_STATE::CONFIGURE:
            context->changeState(Configure::getInstance());
            break;
        case NEXT_STATE::EXIT:
            context -> Exit();
        default:
            break;
    }
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
