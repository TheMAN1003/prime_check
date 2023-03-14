#ifndef NTA_LAB_1_ALGORITHMS_H
#define NTA_LAB_1_ALGORITHMS_H

#define ll long long

#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <vector>

namespace algo {
    ll count(ll n);
    ll digit(ll n, int position);
    ll find_r(ll mod, ll number);
    ll trial(ll n);
    ll function(ll x, ll mod);
    ll gcd(ll a, ll b);
    ll pollard(ll n);
    bool MillerRabin(ll p);
    ll powerMod(ll x, ll pow,ll mod)
} // algo

#endif //NTA_LAB_1_ALGORITHMS_H
