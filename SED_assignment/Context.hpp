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
    State *_state;
public:
    Context();
    void Execute();
    void changeState(State *state);
};

#endif /* Context_hpp */
