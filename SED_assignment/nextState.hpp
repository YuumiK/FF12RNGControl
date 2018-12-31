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
    EXIT,
    CALIBRATION,
    DETERMINATION,
    ADJUSTMENT,
    CONFIGURE,
    MENU,
    STATE_MAX,
};
#endif /* nextState_hpp */
