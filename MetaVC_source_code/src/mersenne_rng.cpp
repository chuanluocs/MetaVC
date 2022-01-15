#ifndef _MERSENNE_RNG_CPP
#define _MERSENNE_RNG_CPP

#include "mersenne_rng.h"

Mersenne_rng::Mersenne_rng()
{
    mt_rand.seed(time(0));
    return;
}

void Mersenne_rng::seed(int seed)
{
    mt_rand.seed(seed);
    return;
}

unsigned int Mersenne_rng::next32()
{
    unsigned int ret = mt_rand();
    return ret;
}

int Mersenne_rng::next31()
{
    int ret = (int)(next32() >> 1);
    return ret;
}

int Mersenne_rng::next(int bound)
{
    long long value = mt_rand();
    int ret = (int)(value % bound);
    return ret;
}

double Mersenne_rng::nextClosed()
{
    unsigned int a = next32() >> 5, b = next32() >> 6;
    return (a * 67108864.0 + b) * (1.0/9007199254740991.0); 
}

double Mersenne_rng::nextHalfOpen()
{ 
    unsigned int a = next32() >> 5, b = next32() >> 6;
    return (a * 67108864.0 + b) * (1.0/9007199254740992.0); 
}

double Mersenne_rng::nextOpen()
{ 
    unsigned int a = next32() >> 5, b = next32() >> 6;
    return (0.5 + a * 67108864.0 + b) * (1.0/9007199254740991.0); 
} 

#endif
