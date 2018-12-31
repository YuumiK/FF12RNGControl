//
//  implementedStates.hpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#ifndef implementedStates_hpp
#define implementedStates_hpp

#include "State.hpp"
#include <stdlib.h>

class Determine : public State{
public:
    void execute(RNG_base &rng, OutputComponent &output);
    void nextState(Context *context);
    static State *getInstance()
    {
        static Determine singleton;
        return &singleton;
    }
};

class Mainmenu : public State{
private:
    int count;
public:
    Mainmenu();
    void execute(RNG_base &rng, OutputComponent &output);
    void nextState(Context *context);
    static State *getInstance()
    {
    	static Mainmenu singleton;
    	return &singleton;
    }
};

#endif /* implementedStates_hpp */
