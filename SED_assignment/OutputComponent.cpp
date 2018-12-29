//
//  OutputComponent.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/28.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "OutputComponent.hpp"


void OutputComponent::printMessage(const std::string message)
{
    std::cout << message << std::endl;
}
int OutputComponent::getIntegerText(const std::string message, int max, int min)
{
    std::cout << message << ":";
    std::string input;
    std::cin >> input;
    while(!std::all_of(input.cbegin(), input.cend(), isdigit))
    {
        std::cout << "unexpected input" << std::endl;
        std::cout << message << ":";
        std::cin >> input;
    }
    return stoi(input);
}

bool OutputComponent::getYNText(const std::string message)
{
    std::cout << message << ":";
    std::string input;
    std::cin >> input;
    char initial = tolower(input[0]);
    while(!(input.size() == 1) || !( initial == 'y' || initial == 'n') )//一文字+islowerしてYかN
    {
        std::cout << "unexpected input" << std::endl;
        std::cout << message << ":";
        std::cin >> input;
        initial = tolower(input[0]);
    }
    return (initial == 'y' ? true : false);
}
void OutputComponent::printRNTable(int count, RNG_base &rngbase)
{
    unsigned int currentPosition = rngbase.getCurrentPosition();
    std::vector<unsigned long> rnlist = rngbase.getRNGlist(count);
    
    
    int widthPos = (int)std::to_string(currentPosition + rnlist.size() - 1).length();
    int widthRN = (int)std::to_string(UINT_MAX).length();
    
    std::cout <<        std::setfill(' ') << std::setw(0) << "POSITION";
    std::cout << ":" << std::setfill(' ') << std::setw(widthPos) << "#";
    std::cout << ":" << std::setfill(' ') << std::setw(widthRN) << "RNG" << std::endl;
    std::cout << std::setfill('-') << std::setw(8 + 1 + widthPos + 1 + widthRN) << "-" << std::endl;
    
    for(int i = 0; i < rnlist.size(); i++)
    {
        std::cout <<        std::setfill(' ') << std::setw(8)        << (i == 0 ? "USED" : (i == 1 ? ">" : " "));
        std::cout << ":" << std::setfill('0') << std::setw(widthPos) << (currentPosition + i);
        std::cout << ":" << std::setfill('0') << std::setw(widthRN)  << rnlist[i] << std::endl;
    }
}
