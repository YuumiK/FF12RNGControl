//
//  main.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/26.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "MT.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    MT mt;
    mt.shiftRNG(1000);
    mt.shiftRNG(-900);
        
    return 0;
}
