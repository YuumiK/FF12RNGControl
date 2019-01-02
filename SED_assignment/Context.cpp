//
//  Context.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "Context.hpp"
#include "State.hpp"
#include "implementedStates.hpp"

#include "MT.hpp"

Context::Context()
{
    importParameters();
    _state = new Calibration();
}
void Context::importParameters()
{
    parameters.insert(std::make_pair(PARAM_MIN, -1));
    parameters.insert(std::make_pair(CURE_MAGICIAN_LEVEL, 66));
    parameters.insert(std::make_pair(PARAM_MIN, -1));
    parameters.insert(std::make_pair(CURE_MAGICIAN_MAGIC, 99));
    parameters.insert(std::make_pair(CURE_MAGICIAN_MAGNIFICATION, 1.5f));
    parameters.insert(std::make_pair(CURE_BASE_MAGIC, 20));
    parameters.insert(std::make_pair(TREASUREPOP_PROB, 1));
    parameters.insert(std::make_pair(TREASUREPOP_NUM_OF_USE_RN, 2));
    parameters.insert(std::make_pair(TREASUREPOP_NUM_OF_ENTIRE_USE_RN, 13));
    parameters.insert(std::make_pair(TREASUREGET_PROB_OF_GILL, 95));
    parameters.insert(std::make_pair(TREASUREGET_PROB_OF_RARE, 10));
    parameters.insert(std::make_pair(TREASUREGET_WHAT_NEED, NEED_RARE));
    parameters.insert(std::make_pair(LVUP_CURRENT_LV, 1));
    parameters.insert(std::make_pair(RN_MOD_X, 100));
    parameters.insert(std::make_pair(RN_MOD_THRESHOLD, 6));
    parameters.insert(std::make_pair(RN_MOD_NUM_OF_ENTIRE_USE_RN, 3));
    parameters.insert(std::make_pair(CONFIG_DISPLAY_RN, 10));
    parameters.insert(std::make_pair(PARAM_MAX, -1));
}
void Context::alternateParameters()
{
    
}
float Context::getParameter(PARAMETERS p)
{
    return parameters.at(p);
}
void Context::setParameter(PARAMETERS p, float f)
{
    parameters[p] = f;
}

void Context::printParameters()
{
    for(auto itr = parameters.begin(); itr != parameters.end(); ++itr){
        OutputComponent::printMessage(std::to_string(itr->first) + ":" + std::to_string((int)itr->second));
    }
}
void Context::Exit()
{
    alternateParameters();
    exit(0);
}

void Context::Execute()
{
    MT mt;
    while (1) {
        _state -> execute(mt, this);
        _state -> nextState(this);
    }
}

void Context::changeState(State *state)
{
    _state = state;
}
