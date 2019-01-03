//
//  main.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/26.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "MT.hpp"
#include "OutputComponent.hpp"
#include "Context.hpp"

int main(int argc, const char * argv[]) {
    Context c;
    c.Execute();
    return 0;
}

/*
 int cure1(unsigned long RNG)
 {
 int magic = 99;
 int lv = 66;
 double result = 20 + (RNG % (int)(20 * 12.5)) / 100.0;
 return (int)(result * (magic * (magic + lv)/256.0 + 2.0) * 1.5);
 }
 int cure2(unsigned long RNG)
 {
 int magic = 99;
 int lv = 99;
 double result = 20 + (RNG % (int)(20 * 12.5)) / 100.0;
 return (int)(result * (magic * (magic + lv)/256.0 + 2.0) * 1.5);
 }
 bool treasure(unsigned long RNG)
 {
 return (RNG % 100 < 6);
 }
 
 MT mt;
 OutputComponent oc;
 
 std::vector<int> curelist;
 curelist.push_back(2047);
 curelist.push_back(2126);
 curelist.push_back(2192);
 
 curelist.push_back(2589);
 curelist.push_back(2436);
 curelist.push_back(2629);
 
 oc.printMessage(mt.determinePosition(cure2, curelist, 1) ? "found" : "not found");
 oc.printRNTable(30, mt);
 //mt.search(treasure, 1000);
 std::cout << oc.getIntegerText("test int", INT_MAX, INT_MIN) << std::endl;
 std::cout << oc.getYNText("test char") << std::endl;
 */
