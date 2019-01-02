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
#include <map>

class State;

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
static std::string toString(PARAMETERS p)
{
    std::string s;
    switch (p) {
        case CURE_MAGICIAN_LEVEL:
            s = "CURE_MAGICIAN_LEVEL";
            break;
        case CURE_MAGICIAN_MAGIC:
            s = "CURE_MAGICIAN_MAGIC";
            break;
        case CURE_MAGICIAN_MAGNIFICATION:
            s = "CURE_MAGICIAN_MAGNIFICATION";
            break;
        case CURE_BASE_MAGIC:
            s = "CURE_BASE_MAGIC";
            break;
        case TREASUREPOP_PROB:
            s = "TREASUREPOP_PROB";
            break;
        case TREASUREPOP_NUM_OF_USE_RN:
            s = "TREASUREPOP_NUM_OF_CONSUME_RN";
            break;
        case TREASUREPOP_NUM_OF_ENTIRE_USE_RN:
            s = "TREASUREPOP_NUM_OF_ENTIRE_CONSUME_RN";
            break;
        case TREASUREGET_PROB_OF_GILL:
            s = "TREASUREGET_PROB_OF_GILL";
            break;
        case TREASUREGET_PROB_OF_RARE:
            s = "TREASUREGET_PROB_OF_RARE";
            break;
        case TREASUREGET_WHAT_NEED:
            s = "TREASUREGET_WHAT_NEED";
            break;
        case LVUP_CURRENT_LV:
            s = "LVUP_CURRENT_LV";
            break;
        case RN_MOD_X:
            s = "RN_MOD_X";
            break;
        case RN_MOD_THRESHOLD:
            s = "RN_MOD_THRESHOLD";
            break;
        case RN_MOD_NUM_OF_ENTIRE_USE_RN:
            s = "RN_MOD_NUM_OF_ENTIRE_CONSUME_RN";
            break;
        case CONFIG_DISPLAY_RN:
            s = "CONFIG_DISPLAY_RN";
            break;
        default:
            s = "";
            break;
    }
    return s;
}
enum WHAT_NEED{
    NEED_MIN,
    NEED_GILL,
    NEED_COMMON,
    NEED_RARE,
    NEED_MAX,
};

class Context{
public:
    Context();
    float getParameter(PARAMETERS p);
    void setParameter(PARAMETERS p, float f);
    void printParameters();
    void Exit();
    void Execute();
    void changeState(State *state);
private:
    std::map<PARAMETERS, float> parameters;
    int HP_MPMAX[100][2];
    
    void importParameters();
    void alternateParameters();
    State *_state;
};

#endif /* Context_hpp */
