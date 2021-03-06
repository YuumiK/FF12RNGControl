//
//  Context.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/29.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "Context.hpp"


Context::Context()
{
    importParameters();
    _state = new Mainmenu();
}
Context::~Context()
{
    Exit();
}
void Context::importParameters()
{
    std::ifstream reading_file;
    reading_file.open(filename, std::ios::in);
    
    std::string reading_line_buffer;
    
    std::cout << "reading " << filename << "..." << std::endl;
    
    int count=0;
    while (!reading_file.eof())
    {
        // read by line
        std::getline(reading_file, reading_line_buffer);
        
        // read by delimiter on reading "one" line
        const char delimiter = ',';
        std::string separated_string_buffer;
        std::istringstream line_separater(reading_line_buffer);
        std::getline(line_separater, separated_string_buffer, delimiter);
        
        if(!separated_string_buffer.empty()) parameters.insert(std::make_pair(static_cast<PARAMETERS>(count++), std::stof(separated_string_buffer)));
    }
    reading_file.close();
    //HPMP
    const std::string hpmpfilename = "HPMPmodby.csv";
    reading_file.open(hpmpfilename, std::ios::in);
    
    std::cout << "reading " << hpmpfilename << "..." << std::endl;
    
    count=0;
    while (!reading_file.eof())
    {
        // read by line
        std::getline(reading_file, reading_line_buffer);
        
        // read by delimiter on reading "one" line
        const char delimiter = ',';
        std::string separated_string_buffer;
        std::istringstream line_separater(reading_line_buffer);
        
        while(std::getline(line_separater, separated_string_buffer, delimiter))
        {
            if(count == 0)
            {
                HPMaxMod.push_back(std::stoi(separated_string_buffer));
            }
            else if(count == 1)
            {
                MPMaxMod.push_back(std::stoi(separated_string_buffer));
            }
        }
        count++;
    }
}
void Context::alternateParameters()
{
    std::ofstream writing_file;
    writing_file.open(filename, std::ios::out);
    
    if(! writing_file.is_open())
    {
        std::cout << "open " << filename << " failed" << std::endl;
        // exit だけでなく return の戻り値としても使用できる。
        return;
    }
    else
    {
        std::cout << "writing " << filename << "..." << std::endl;
        
        for(auto itr = parameters.begin(); itr != parameters.end(); ++itr){
            writing_file << std::to_string(itr->second) << std::endl;
        }
    }
}
void Context::Exit()
{
    alternateParameters();
    exit(0);
}

void Context::Execute()
{
    MT mt;
    while (1) {
        _state -> execute(mt, this);
        _state -> nextState(this);
    }
}

void Context::changeState(State *state)
{
    _state = state;
}

float Context::getParameter(PARAMETERS p){ return parameters.at(p);}
void Context::setParameter(PARAMETERS p, float f){parameters[p] = f;}
int Context::getHPmax(int lv){return HPMaxMod.at(lv - 1);}
int Context::getMPmax(int lv){return MPMaxMod.at(lv - 1);}

/*
 parameters.insert(std::make_pair(PARAM_MIN, -1));
 parameters.insert(std::make_pair(CURE_MAGICIAN_LEVEL, 66));
 parameters.insert(std::make_pair(CURE_MAGICIAN_MAGIC, 99));
 parameters.insert(std::make_pair(CURE_MAGICIAN_MAGNIFICATION, 1.5f));
 parameters.insert(std::make_pair(CURE_BASE_MAGIC, 20));
 parameters.insert(std::make_pair(TREASUREPOP_PROB, 1));
 parameters.insert(std::make_pair(TREASUREPOP_NUM_OF_USE_RN, 2));
 parameters.insert(std::make_pair(TREASUREPOP_NUM_OF_ENTIRE_USE_RN, 13));
 parameters.insert(std::make_pair(TREASUREGET_PROB_OF_GILL, 95));
 parameters.insert(std::make_pair(TREASUREGET_PROB_OF_RARE, 10));
 parameters.insert(std::make_pair(TREASUREGET_WHAT_NEED, NEED_RARE));
 parameters.insert(std::make_pair(LVUP_CURRENT_LV, 1));
 parameters.insert(std::make_pair(RN_MOD_X, 100));
 parameters.insert(std::make_pair(RN_MOD_THRESHOLD, 6));
 parameters.insert(std::make_pair(RN_MOD_NUM_OF_ENTIRE_USE_RN, 3));
 parameters.insert(std::make_pair(PARAM_MAX, -1));*/
