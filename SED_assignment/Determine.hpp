//
//  Determine.hpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#ifndef Determine_hpp
#define Determine_hpp

#include "State.hpp"
struct Determine : public State{
    Determine();
    ~Determine();
    
    virtual State execute(State sts);
};

#endif /* Determine_hpp */
