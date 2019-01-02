//
//  MT.cpp
//  SED_assignment
//
//  Created by Yuumi Konishi on 2018/12/26.
//  Copyright © 2018 KoniKoni. All rights reserved.
//

#include "MT.hpp"


MT::MT()
{
    initializeAlgorithm();
}
MT::~MT()
{
    
}

void MT::sgenrand(unsigned long seed)
{
    /* setting initial seeds to mt[N] using         */
    /* the generator Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming */
    /*    Vol. 2 (2nd Ed.), pp102]                  */
    mt[0]= seed & 0xffffffff;
    for (mti=1; mti<N; mti++)
    {
        mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
    }
}

void MT::initializeAlgorithm()
{
    sgenrand(4537);
}
void MT::forward()
{
    unsigned long y;
    static unsigned long mag01[2]={0x0, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */
    
    if (mti >= N)
    { /* generate N words at one time */
        int kk;
        
        for (kk = 0; kk < N - M; kk++)
        {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (; kk < N-1; kk++)
        {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
        
        mti = 0;
    }
    
    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    
    setCurrentRN(y);
    add1CurrentPosition();
}

void MT::backward()
{
    assert(getCurrentPosition() >= 0);
    unsigned long y;
    unsigned long a32;
    static unsigned long mag01[2]={0x0, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */
    
    --mti;
    if(mti == 0)
    {
        mti = N;
        int kk;
        
        a32 = (mt[M-1] ^ mt[N-1])>>31;
        y = mt[M-1] ^ mag01[a32] ^ mt[N-1];
        y = y << 1 | a32;
        mt[N-1] = y & UPPER_MASK;
        
        for(kk = N-1 - 1; kk >= N-M; kk--)
        {
            a32 = (mt[kk + (M-N)] ^ mt[kk])>>31;
            y = mt[kk + (M-N)] ^ mag01[a32] ^ mt[kk];
            y = y << 1 | a32;
            mt[kk] = y & UPPER_MASK;
        	mt[kk+1] |= y & LOWER_MASK;
        }
        
        for (; kk >= 0; kk--)
        {
            a32 = (mt[kk + M] ^ mt[kk])>>31;
            y = mt[kk + M] ^ mag01[a32] ^ mt[kk];
            y = y << 1 | a32;
            mt[kk] = y & UPPER_MASK;
            mt[kk+1] |= y & LOWER_MASK;
        }
        
        a32 = (mt[M-1] ^ mt[N-1])>>31;
        y = mt[M-1] ^ mag01[a32] ^ mt[N-1];
        y = y << 1 | a32;
        mt[N-1] |= y & LOWER_MASK;
    }
    
    y = mt[mti - 1];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    
    setCurrentRN(y);
    sub1CurrentPosition();
}
