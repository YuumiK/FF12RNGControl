//
//  implementedStates.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "implementedStates.hpp"


//Calibration
void Calibration::execute(RNG_base &rng, OutputComponent &output, Context *context)
{
    output.printMessage("Cast cure and enter the amount of restored HP");
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
        cure = output.getIntegerText("cure"+std::to_string(curelist.size()+1), INT_MAX, INT_MIN);
        curelist.push_back(cure);
    }
    
    unsigned long timeoutMillsec = 1;
    while(!rng.determinePosition(calculateCure, curelist, magic, level, timeoutMillsec))
    {
        cure = 0;
        cure = output.getIntegerText("cure"+std::to_string(curelist.size()+1), INT_MAX, INT_MIN);
        curelist.push_back(cure);
    }
    output.printRNTable(context->getParameter(CONFIG_DISPLAY_RN), rng);
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
void Mainmenu::execute(RNG_base &rng, OutputComponent &output, Context *context)
{
    output.printMessage("Mainmenu 1:Calibration,2:Determination,3:Adjustment,4:Config,0:Exit");
    next = (NEXT_STATE)output.getNextState("Next command");
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
void Determine::execute(RNG_base &rng, OutputComponent &output, Context *context)
{
    output.printMessage("Determine execute");
}
void Determine::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}

//Adjustment
void Adjustment::execute(RNG_base &rng, OutputComponent &output, Context *context)
{
    int n = output.getIntegerText("enter the amount of shift",INT_MAX, INT_MIN);
    rng.shiftRNG(n);
    output.printRNTable(context->getParameter(CONFIG_DISPLAY_RN), rng);
}
void Adjustment::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}

//Configure
void Configure::execute(RNG_base &rng, OutputComponent &output, Context *context)
{
    output.printMessage("Configure execute");
    context -> printParameters(output);
    PARAMETERS changeParam = output.getParam("Choose which to change");
    //input方法の工夫(getFloatTextの実装、)
}
void Configure::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}
