//
//  MT.hpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/26.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#ifndef MT_hpp
#define MT_hpp

#include <iostream>
#include "RNG_base.hpp"
class MT : public RNG_base{

private:
    //period parameters
    static const int N = 624;
    static const int M = 397;
    static const unsigned long MATRIX_A = 0x9908b0df;
    static const unsigned long UPPER_MASK = 0x80000000;
    static const unsigned long LOWER_MASK = 0x7fffffff;
    
    //tempering parameters
    static const unsigned long TEMPERING_MASK_B = 0x9d2c5680;
    static const unsigned long TEMPERING_MASK_C = 0xefc60000;
    
    inline unsigned long TEMPERING_SHIFT_U(unsigned long y)  {return y >> 11;}
    inline unsigned long TEMPERING_SHIFT_S(unsigned long y)  {return y <<  7;}
    inline unsigned long TEMPERING_SHIFT_T(unsigned long y)  {return y << 15;}
    inline unsigned long TEMPERING_SHIFT_L(unsigned long y)  {return y >> 18;}
    
    unsigned long mt[N]; /* the array for the state vector  */
    int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
    void sgenrand(unsigned long seed);
    
    unsigned long beforeMtN;
    
protected:
    void initializeAlgorithm();
    void forward();
    void backward();
    
public:
    MT();
    ~MT();
};

#endif /* MT_hpp */
