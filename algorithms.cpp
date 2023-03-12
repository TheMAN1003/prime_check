#include "algorithms.h"


ll algo::function(long long x, ll mod) {
    return (x*x+1)%mod;
}

ll algo::gcd(long long a, long long b) {
    ll d = 1;
    while (d!=0){
        d=a%b;
        a=b;
        b=d;
    }
    return a;
}

ll algo::pollard(long long n) {
    ll x = 1;
    ll y = 1;
    ll d = 1;
    while(d==1){
        x = function(x, n);
        y = function(function(y, n), n);
        d = gcd(abs(x-y), n);
        if(x==y){
            x++;
            y=x;
            d=1;
        }
        if(d!=1){
            return d;
        }
    }
}