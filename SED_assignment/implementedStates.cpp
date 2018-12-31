//
//  implementedStates.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "implementedStates.hpp"


void Determine::execute(RNG_base &rng, OutputComponent &output)
{
    output.printMessage("Determine execute");
}
void Determine::nextState(Context *context)
{
    context->changeState(Mainmenu::getInstance());
}



Mainmenu::Mainmenu()
{
    count = 0;
}
void Mainmenu::execute(RNG_base &rng, OutputComponent &output)
{
    output.printMessage("Mainmenu execute");
    count++;
    if(count == 10) exit(0);
}

void Mainmenu::nextState(Context *context)
{
    context->changeState(Determine::getInstance());
}
