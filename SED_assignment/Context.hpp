//
//  Context.hpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#ifndef Context_hpp
#define Context_hpp

#include "State.hpp"

class State;

class Context{
public:
    enum PARAMETERS{
        PARAM_MIN,
        
        CURE_MAGICIAN_LEVEL,
        CURE_MAGICIAN_MAGIC,
        CURE_MAGICIAN_MAGNIFICATION,
        CURE_BASE_MAGIC,
        
        TREASUREPOP_PROB,
        TREASUREPOP_NUM_OF_USE_RN,
        TREASUREPOP_NUM_OF_ENTIRE_USE_RN,
        
        TREASUREGET_PROB_OF_GILL,
        TREASUREGET_PROB_OF_RARE,
        TREASUREGET_WHAT_NEED,
        
        LVUP_CURRENT_LV,
        
        RN_MOD_X,
        RN_MOD_THRESHOLD,
        RN_MOD_NUM_OF_ENTIRE_USE_RN,
        CONFIG_DISPLAY_RN,
        PARAM_MAX,
    };
    Context();
    float getParameters(PARAMETERS p);
    void setParameters(PARAMETERS p, float f);
    void Exit();
    void Execute();
    void changeState(State *state);
private:
    float parameters[PARAM_MAX+1];
    int HP_MPMAX[100][2];
    
    void importParameters();
    void alternateParameters();
    State *_state;
};

#endif /* Context_hpp */
