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
    std::cin >> input; std::cin.clear();
    int num;
    while(1){
        try {
            num = std::stoi(input);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "unexpected input" << std::endl;
            std::cout << message << ":";
            std::cin >> input; std::cin.clear();
        }
        catch (const std::out_of_range& e) {
            std::cout << "out of range input" << std::endl;
            std::cout << message << ":";
            std::cin >> input; std::cin.clear();
        }
        if(min < num && max > num) break;
        else
        {
            std::cout << "out of range input" << std::endl;
            std::cout << message << ":";
            std::cin >> input; std::cin.clear();
        }
    }
    return num;
}

float OutputComponent::getFloatText(const std::string message, float max, float min)
{
    std::cout << message << ":";
    std::string input;
    std::cin >> input; std::cin.clear();
    float num;
    while(1){
        try {
            num = std::stof(input);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "unexpected input" << std::endl;
            std::cout << message << ":";
            std::cin >> input; std::cin.clear();
        }
        catch (const std::out_of_range& e) {
            std::cout << "out of range input" << std::endl;
            std::cout << message << ":";
            std::cin >> input; std::cin.clear();
        }
        if(min < num && max > num) break;
        else
        {
            std::cout << "out of range input" << std::endl;
            std::cout << message << ":";
            std::cin >> input; std::cin.clear();
        }
    }
    return num;
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
        std::cin >> input; std::cin.clear();
        initial = tolower(input[0]);
    }
    return (initial == 'y' ? true : false);
}
void OutputComponent::printParameters()
    {
        for(int p = PARAM_MIN; p<PARAM_MAX; ++p){
            PARAMETERS pp = static_cast<PARAMETERS>(p);
            printMessage(std::to_string(p) + ":"+ ((p==PARAM_MIN) ? "Change nothing" : (toString(pp) + "=" + std::to_string(static_cast<int>(Context::getParameter(pp))))) );
        }
    }

PARAMETERS OutputComponent::getParam(const std::string message)
{
    int min = static_cast<int>(PARAM_MIN)-1;
    int max = static_cast<int>(PARAM_MAX);
    int num = getIntegerText(message, max, min);
    return static_cast<PARAMETERS>(num);
}

void OutputComponent::printRNTable(RNG_base &rngbase, int count)
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
        std::cout <<        std::setfill(' ') << std::setw(8)        << (i == 0 ? "CONSUMED" : (i == 1 ? ">" : " "));
        std::cout << ":" << std::setfill('0') << std::setw(widthPos) << (currentPosition + i);
        std::cout << ":" << std::setfill('0') << std::setw(widthRN)  << rnlist[i] << std::endl;
    }
}
