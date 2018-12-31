//
//  nextState.hpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2019/01/01.
//  Copyright © 2019 KoniKoni. All rights reserved.
//

#ifndef nextState_hpp
#define nextState_hpp

enum class NEXT_STATE{
    STATE_MIN = -1,
    EXIT = 0,
    CALIBRATION = 1,
    MENU = 2,
    DETERMINATION = 3,
    ADJUSTMENT = 4,
    CONFIGURE = 5,
    STATE_MAX = 6,
};
#endif /* nextState_hpp */
