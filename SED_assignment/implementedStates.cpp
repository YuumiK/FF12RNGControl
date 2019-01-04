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
        OutputComponent::printMessage("time out. your input or parameters might be invalid. continue to search?");
        if(!OutputComponent::getYNText("Y/N")) break;
        else
        {
            cure = 0;
        	cure = OutputComponent::getIntegerText("cure"+std::to_string(curelist.size()+1), INT_MAX, INT_MIN);
        	curelist.push_back(cure);
    	}
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

bool isTreasureAppear(std::vector<unsigned long> RNs)//RNs[0] = currentPosition(already consumed). RNs[size-1] = currentposition+used in this check
{
    return (RNs[RNs.size()-1]%100) < Context::getParameter(TREASUREPOP_PROB);
}
bool isAbleToGetDesireTreasure(std::vector<unsigned long> RNs)
{
    return ((RNs[1]%100) >= Context::getParameter(TREASUREGET_PROB_OF_GILL) && (RNs[2]%100) >= (100 - Context::getParameter(TREASUREGET_PROB_OF_RARE)));
}
bool isAbleToIncreaseMaximumStatus(std::vector<unsigned long> RNs)
{
    assert(Context::getParameter(LVUP_CURRENT_LV) != 99);
    auto pow10 = [](int a) { int ans = 1;for(int i=0;i<a; i++) ans *= 10;return ans; };
    int hpModBy = Context::getHPmax(Context::getParameter(LVUP_CURRENT_LV)+1);
    int hpThreshold = hpModBy/pow10(std::log10(hpModBy)+1 - 1) * pow10(log10(hpModBy)+1 - 1);
    int mpModBy = Context::getMPmax(Context::getParameter(LVUP_CURRENT_LV)+1);
    int mpThreshold = mpModBy - 100;
    return ((RNs[1]%hpModBy) >= hpThreshold && (RNs[2]%mpModBy) >= mpThreshold);
}
bool isLowerThanThreshold(std::vector<unsigned long> RNs)
{
    return (RNs[1]%(int)(Context::getParameter(RN_MOD_X))) < Context::getParameter(RN_MOD_THRESHOLD);
}

//return how many hits will be provided from current rng position
int howManyRNConsumedByHit(RNG_base &rng){
    std::vector<unsigned long> RNs = rng.getRNGlist(1 + 5 + 11);
    if(RNs[5]%100 < (int)(5*0.7))
    {
        int conbo = 2;
        for(int i = 6; i < RNs.size(); i++)
        {
            if(RNs[i]%100 < 8) conbo++;
        }
        return 9*conbo+12;
    }
    else return 10;
}
void printHowToShift(RNG_base &rng, int shift)
{
    if(shift <= 0) return;
    else if(shift < 10) OutputComponent::printMessage("cure " + std::to_string(shift) + "times.");
    else
    {
        int consumeByHit = howManyRNConsumedByHit(rng);
        if(shift < consumeByHit)
        {
            OutputComponent::printMessage("cure.");
            printHowToShift(rng, shift - 1);
        }
        else
        {
            OutputComponent::printMessage("Hit yourself by hand.");
            printHowToShift(rng, shift - consumeByHit);
        }
    }
}

//Determine
void Determine::execute(RNG_base &rng, Context *context)
{
    OutputComponent::printMessage("Choose which to control 1:treasure appear,2:treasure obtain,3:HPMP max,4:control modulo,0:Nothing");
    CONTROL_EVENT event;
    int min = static_cast<int>(CONTROL_EVENT::EVENT_MIN) - 1;
    int max = static_cast<int>(CONTROL_EVENT::EVENT_MAX);
    event = static_cast<CONTROL_EVENT>(OutputComponent::getIntegerText("Command", max, min));
    if (event == CONTROL_EVENT::HPMP_MAX && Context::getParameter(LVUP_CURRENT_LV) == 99) OutputComponent::printMessage("No need to control RNG. You're already level up the character to 99.");
    else if(event == CONTROL_EVENT::EVENT_MIN){}
    else
    {
        std::function<bool (std::vector<unsigned long>)> control;
        int numOfRequireRNs = 0;
        int moveRNGs = 0;
        unsigned long timeoutMillsec = 1;
        switch (event) {
            case CONTROL_EVENT::TREASURE_APPEAR:
                control = isTreasureAppear;
                numOfRequireRNs = Context::getParameter(TREASUREPOP_NUM_OF_USE_RN);
                moveRNGs += Context::getParameter(TREASUREPOP_NUM_OF_ENTIRE_USE_RN);
                break;
            case CONTROL_EVENT::TREASURE_OBTAIN:
                control = isAbleToGetDesireTreasure;
                numOfRequireRNs = 2;
                moveRNGs += 2;
                break;
            case CONTROL_EVENT::HPMP_MAX:
                control = isAbleToIncreaseMaximumStatus;
                numOfRequireRNs = 2;
                moveRNGs += 2;
                break;
            case CONTROL_EVENT::CONTROL_MODULO:
                control = isLowerThanThreshold;
                numOfRequireRNs = 1;
                moveRNGs += 1;
                break;
            default:
                break;
        }
        unsigned int prevPosition = rng.getCurrentPosition();
        unsigned int idealPosition = rng.search(control, numOfRequireRNs, timeoutMillsec);
        OutputComponent::printMessage("You need to move " + std::to_string(idealPosition - prevPosition) + "RNs. Here's how.");
        printHowToShift(rng, idealPosition - prevPosition);
        rng.shiftRNG(idealPosition - prevPosition);
        
        OutputComponent::printMessage("Here is the ideal RNG state for the event you desire:");
        OutputComponent::printRNTable(moveRNGs+1, rng);
        rng.shiftRNG(moveRNGs);
    }
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
