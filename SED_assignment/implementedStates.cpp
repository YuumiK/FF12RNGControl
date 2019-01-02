//
//  implementedStates.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "implementedStates.hpp"


//Calibration
void Calibration::execute(RNG_base &rng, Context *context)
{
    OutputComponent::printMessage("Cast cure and enter the amount of restored HP");
    std::vector<int> curelist;
    
    const int magic = context->getParameter(CURE_MAGICIAN_MAGIC);
    const int level = context->getParameter(CURE_MAGICIAN_LEVEL);
    std::function<int (unsigned long, int, int)> calculateCure = [](unsigned long RN, int magic, int level)
    {
        double result = 20 + (RN % (int)(20 * 12.5)) / 100.0;
        return (int)(result * (magic * (magic + level)/256.0 + 2.0) * 1.5);
    };
    
    int cure;
    for(int i=0; i<3; i++)
    {
        cure = OutputComponent::getIntegerText("cure"+std::to_string(curelist.size()+1), INT_MAX, INT_MIN);
        curelist.push_back(cure);
    }
    
    unsigned long timeoutMillsec = 1;
    while(!rng.determinePosition(calculateCure, curelist, magic, level, timeoutMillsec))
    {
        cure = 0;
        cure = OutputComponent::getIntegerText("cure"+std::to_string(curelist.size()+1), INT_MAX, INT_MIN);
        curelist.push_back(cure);
    }
    OutputComponent::printRNTable(context->getParameter(CONFIG_DISPLAY_RN), rng);
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
void Mainmenu::execute(RNG_base &rng, Context *context)
{
    OutputComponent::printMessage("Mainmenu 1:Calibration,2:Determination,3:Adjustment,4:Config,0:Exit");
    next = OutputComponent::getNextState("Next command");
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
void Determine::execute(RNG_base &rng, Context *context)
{
    OutputComponent::printMessage("Determine execute");
    
}
void Determine::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}

//Adjustment
void Adjustment::execute(RNG_base &rng, Context *context)
{
    int n = OutputComponent::getIntegerText("enter the amount of shift",INT_MAX, INT_MIN);
    rng.shiftRNG(n);
    OutputComponent::printRNTable(context->getParameter(CONFIG_DISPLAY_RN), rng);
}
void Adjustment::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}

//Configure
void Configure::execute(RNG_base &rng, Context *context)
{
    OutputComponent::printMessage("Configure execute");
    context -> printParameters();
    PARAMETERS changeParam = OutputComponent::getParam("Choose which to change");
    switch (changeParam) {
        case CURE_MAGICIAN_MAGNIFICATION:
            context->setParameter(changeParam, OutputComponent::getFloatText("change to", 2.0f, 0.0f));
            break;
            
        default:
            context->setParameter(changeParam, OutputComponent::getIntegerText("change to", INT_MAX, INT_MIN));
            break;
    }
}
void Configure::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}
