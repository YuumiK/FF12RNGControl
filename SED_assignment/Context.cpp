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
    _state = new Determine();
}

void Context::Execute()
{
    MT mt;
    OutputComponent output;
    while (1) {
        _state -> execute(mt, output);
        _state -> nextState(this);
    }
}

void Context::changeState(State *state)
{
    _state = state;
}