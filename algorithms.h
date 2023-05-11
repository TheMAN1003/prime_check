#ifndef NTA_LAB_1_ALGORITHMS_H
#define NTA_LAB_1_ALGORITHMS_H

#define ll long long

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <gmpxx.h>

namespace algo
{
    ll trial(ll n);
    ll pollard(ll n);
    bool MillerRabin(ll p);
    std::string methodBrillhartMorrison(ll n,std::vector<ll> primes);
}

#endif //NTA_LAB_1_ALGORITHMS_H
