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
    int next;
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

class Calibration : public State{
private:
public:
    void execute(RNG_base &rng, OutputComponent &output);
    void nextState(Context *context);
    static State *getInstance()
    {
        static Calibration singleton;
        return &singleton;
    }
};

class Adjustment : public State{
private:
public:
    void execute(RNG_base &rng, OutputComponent &output);
    void nextState(Context *context);
    static State *getInstance()
    {
        static Adjustment singleton;
        return &singleton;
    }
};

class Configure : public State{
private:
public:
    void execute(RNG_base &rng, OutputComponent &output);
    void nextState(Context *context);
    static State *getInstance()
    {
        static Configure singleton;
        return &singleton;
    }
};


#endif /* implementedStates_hpp */
