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
    //変数
    int cure_magician_level;
    int cure_magician_magic;
    float cure_magician_magnification;
    int cure_base_magic;
    
    int treasurepop_prob;
    int treasurepop_num_of_use_rn;
    int treasurepop_num_of_entire_use_rn;
    
    int treasureget_prob_of_gill;
    int treasureget_prob_of_rare;
    int treasureget_what_need;
    
    int lvup_current_lv;
    
    int rn_mod_x;
    int rn_mod_threshold;
    int rn_mod_num_of_entire_use_rn;
    
    int config_display_rn;
    
    State *_state;
public:
    Context();
    void importParameters();
    void alternateParameters();
    void Exit();
    void Execute();
    void changeState(State *state);
};

#endif /* Context_hpp */
