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
    
    std::function<int (unsigned long)> calculateCure = [](unsigned long RN)
    {
        double result = 20 + (RN % (int)(20 * 12.5)) / 100.0;
        return (int)(result * (Context::getParameter(CURE_MAGICIAN_MAGIC) * (Context::getParameter(CURE_MAGICIAN_MAGIC) + Context::getParameter(CURE_MAGICIAN_LEVEL))/256.0 + 2.0) * 1.5);
    };
    
    int cure;
    for(int i=0; i<3; i++)
    {
        cure = OutputComponent::getIntegerText("cure"+std::to_string(curelist.size()+1), INT_MAX, INT_MIN);
        curelist.push_back(cure);
    }
    
    unsigned long timeoutMillsec = 1;
    while(!rng.determinePosition(calculateCure, curelist, timeoutMillsec))
    {
        cure = 0;
        cure = OutputComponent::getIntegerText("cure"+std::to_string(curelist.size()+1), INT_MAX, INT_MIN);
        curelist.push_back(cure);
    }
    OutputComponent::printRNTable(Context::getParameter(CONFIG_DISPLAY_RN), rng);
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
    int min = static_cast<int>(NEXT_STATE::STATE_MIN);
    int max = static_cast<int>(NEXT_STATE::STATE_MAX);
    next = static_cast<NEXT_STATE>(OutputComponent::getIntegerText("Command", max, min));
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

bool isTreasureAppear(std::vector<unsigned long> RNs)
{
    return (RNs[0]%100) < Context::getParameter(TREASUREPOP_PROB);
}
bool isAbleToGetDesireTreasure(std::vector<unsigned long> RNs)
{
    return ((RNs[0]%100) >= Context::getParameter(TREASUREGET_PROB_OF_GILL) && (RNs[1]%100) >= (100 - Context::getParameter(TREASUREGET_PROB_OF_RARE)));
}
bool isAbleToIncreaseMaximumStatus(std::vector<unsigned long> RNs)
{
    auto pow10 = [](int a) { int ans = 1;for(int i=0;i<a; i++) ans *= 10;return ans; };
    int hpModBy = Context::getHPmax(Context::getParameter(LVUP_CURRENT_LV));
    int hpThreshold = hpModBy/pow10(std::log10(hpModBy)+1 - 1) * pow10(log10(hpModBy)+1 - 1);
    int mpModBy = Context::getMPmax(Context::getParameter(LVUP_CURRENT_LV));
    int mpThreshold = mpModBy - 100;
    return ((RNs[0]%hpModBy) >= hpThreshold && (RNs[1]%mpModBy) >= mpThreshold);
}
bool isLowerThanThreshold(std::vector<unsigned long> RNs)
{
    return (RNs[0]%(int)(Context::getParameter(RN_MOD_X))) < Context::getParameter(RN_MOD_THRESHOLD);
}

//Determine
void Determine::execute(RNG_base &rng, Context *context)
{
    OutputComponent::printMessage("Choose which to control 1:treasure appear,2:treasure obtain,3:HPMP max,4:control modulo,0:Nothing");
    CONTROL_EVENT event;
    int min = static_cast<int>(CONTROL_EVENT::EVENT_MIN);
    int max = static_cast<int>(CONTROL_EVENT::EVENT_MAX);
    event = static_cast<CONTROL_EVENT>(OutputComponent::getIntegerText("Command", max, min));
    
    std::function<bool (std::vector<unsigned long>)> control;
    int numOfRequireRNs = 0;
    unsigned long timeoutMillsec = 1;
    switch (event) {
        case CONTROL_EVENT::TREASURE_APPEAR:
            control = isTreasureAppear;
            numOfRequireRNs = 1;
            break;
        case CONTROL_EVENT::TREASURE_OBTAIN:
            control = isAbleToGetDesireTreasure;
            numOfRequireRNs = 2;
            break;
        case CONTROL_EVENT::HPMP_MAX:
            control = isAbleToIncreaseMaximumStatus;
            numOfRequireRNs = 2;
            break;
        case CONTROL_EVENT::CONTROL_MODULO:
            control = isLowerThanThreshold;
            numOfRequireRNs = 1;
            break;
        default:
            break;
    }
    unsigned int prevPosition = rng.getCurrentPosition();
    rng.search(control, numOfRequireRNs, timeoutMillsec);
    OutputComponent::printMessage("You need to move " + std::to_string(rng.getCurrentPosition() - prevPosition) + "RNs.");
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
    OutputComponent::printRNTable(Context::getParameter(CONFIG_DISPLAY_RN), rng);
}
void Adjustment::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}

//Configure
void Configure::execute(RNG_base &rng, Context *context)
{
    OutputComponent::printMessage("Configure");
    OutputComponent::printParameters();
    PARAMETERS changeParam = OutputComponent::getParam("Choose which to change");
    switch (changeParam) {
        case CURE_MAGICIAN_MAGNIFICATION:
            Context::setParameter(changeParam, OutputComponent::getFloatText("change to", 2.0f, 0.0f));
            break;
        case PARAM_MIN:
        case PARAM_MAX:
            break;
        default:
            Context::setParameter(changeParam, OutputComponent::getIntegerText("change to", INT_MAX, INT_MIN));
            break;
    }
}
void Configure::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}
