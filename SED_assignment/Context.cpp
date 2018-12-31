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
#include "OutputComponent.hpp"

Context::Context()
{
    importParameters();
    _state = new Calibration();
}
void Context::importParameters()
{
    parameters[PARAM_MIN] = 0;
    parameters[CURE_MAGICIAN_LEVEL] = 99;
    parameters[CURE_MAGICIAN_MAGIC] = 99;
    parameters[CURE_MAGICIAN_MAGNIFICATION] = 1.5f;
    parameters[CURE_BASE_MAGIC] = 20;
    parameters[TREASUREPOP_PROB] = 1;
    parameters[TREASUREPOP_NUM_OF_USE_RN] = 2;
    parameters[TREASUREPOP_NUM_OF_ENTIRE_USE_RN] = 13;
    parameters[TREASUREGET_PROB_OF_GILL] = 95;
    parameters[TREASUREGET_PROB_OF_RARE] = 10;
    parameters[TREASUREGET_WHAT_NEED] = 1;
    parameters[LVUP_CURRENT_LV] = 1;
    parameters[RN_MOD_X] = 100;
    parameters[RN_MOD_THRESHOLD] = 6;
    parameters[RN_MOD_NUM_OF_ENTIRE_USE_RN] = 3;
    parameters[CONFIG_DISPLAY_RN] = 10;
    parameters[PARAM_MAX] = 99;
}
void Context::alternateParameters()
{
    
}
float Context::getParameters(PARAMETERS p)
{
    return parameters[p];
}
void Context::setParameters(PARAMETERS p, float f)
{
    parameters[p] = f;
}
void Context::Exit()
{
    alternateParameters();
    exit(0);
}

void Context::Execute()
{
    MT mt;
    OutputComponent output;
    while (1) {
        _state -> execute(mt, output, this);
        _state -> nextState(this);
    }
}

void Context::changeState(State *state)
{
    _state = state;
}
