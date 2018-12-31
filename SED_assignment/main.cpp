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
#include <iostream>
int magic = 99;
int cure1(unsigned long RNG)
{
    int lv = 66;
    double result = 20 + (RNG % (int)(20 * 12.5)) / 100.0;
    return (int)(result * (magic * (magic + lv)/256.0 + 2.0) * 1.5);
}
int cure2(unsigned long RNG)
{
    int lv = 99;
    double result = 20 + (RNG % (int)(20 * 12.5)) / 100.0;
    return (int)(result * (magic * (magic + lv)/256.0 + 2.0) * 1.5);
}
bool treasure(unsigned long RNG)
{
    return (RNG % 100 < 6);
}

int main(int argc, const char * argv[]) {
    
    /*
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
    
    Context c;
    c.Execute();
    return 0;
}
/*
 ケアル使用者のレベル:99
 ケアル使用者の魔力:99
 ケアルの値 1回目:2589
 ケアルの値 2回目:2436
 ケアルの値 3回目:2629
 現在位置(1-origin):7524
 現在位置再決定:0,レベル最大:1,レア盗み:2,レアトレジャー:3,POP等その他:4,チョコボ:5,終了:9
 4
 トレジャーpop乱数(1スタート):7614
 動かす個数:90
*/
