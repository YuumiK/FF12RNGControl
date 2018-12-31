//
//  State.hpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <iostream>
#include "MT.hpp"
#include "OutputComponent.hpp"
#include "State.hpp"
#include "Context.hpp"


class Context;

//State pattern
class State{
public:
    virtual void execute(RNG_base &rng, OutputComponent &output)=0;
    virtual void nextState(Context *context) = 0;
};
#endif /* State_hpp */
