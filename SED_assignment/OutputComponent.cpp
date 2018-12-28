//
//  OutputComponent.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/28.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "OutputComponent.hpp"


void OutputComponent::printMessage(const string message)
{
    cout << message << endl;
}
/*int OutputComponent::getIntegerText(const string message, int max, int min)
{
    cout << message << ":";
    string input;
    int result;
    while(1)
    {
        cin >> input;
        
    }
}
bool OutputComponent::getYNText(const string message)
{
    cout << message;
    
}*/
void OutputComponent::printRNTable(int count, RNG_base &rngbase)
{
    unsigned int currentPosition = rngbase.getCurrentPosition();
    vector<unsigned long> rnlist = rngbase.getRNGlist(count);
    
    
    int widthPos = (int)to_string(currentPosition + rnlist.size() - 1).length();
    int widthRN = (int)to_string(UINT_MAX).length();
    
    cout <<        setfill(' ') << setw(0) << "POSITION";
    cout << ":" << setfill(' ') << setw(widthPos) << "#";
    cout << ":" << setfill(' ') << setw(widthRN) << "RNG" << endl;
    cout << setfill('-') << setw(8 + 1 + widthPos + 1 + widthRN) << "-" << endl;
    
    for(int i = 0; i < rnlist.size(); i++)
    {
        cout <<        setfill(' ') << setw(8)        << (i == 0 ? "USED" : (i == 1 ? ">" : " "));
        cout << ":" << setfill('0') << setw(widthPos) << (currentPosition + i);
        cout << ":" << setfill('0') << setw(widthRN)  << rnlist[i] << endl;
    }
}
