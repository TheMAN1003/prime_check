#include "algorithms.h"

ll algo::count(ll n) {
    int count = 0;
    while(n != 0){
        n=n/10;
        count++;
    }
    return count;
}

ll algo::digit(ll a, int position) {
    for (int i = 0; i < position; i++){
        a=a/10;
    }
    a=a%10;
    return a;
}

ll algo::find_r(ll mod, ll position){
    int r = 1;
    for(int i=0; i < position; i++){
        r = (r*10)%mod;
    }
    return r;
}

ll algo::trial(long long n) {
    for (int j=2; j < 48; j++) {
        int sum = 0;
        for (int i = 0; i < count(n); i++) {
            sum += (digit(n, i)* find_r(j, i))%j;
        }
        if(sum%j==0){
            return j;
        }
    }
    std::cout << "Trial method was unsuccessful\n" ;
    return -1;
}

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

ll algo::powerMod(ll x, ll pow,ll mod)
{
    ll C = 1;
    for(int i = int(log2(pow)); i >= 0; --i)
    {
        if((pow>>i & 1) == 1)
        {
            C = (C * x)%mod;
        }
        if(i != 0)
            C = (C * C)%mod;
    }
    return C;
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

bool algo::MillerRabin(long long p)
{
    ll k = 1000,j = 0;
    ll d = p - 1, s = 0;
    while (d % 2 == 0)
    {
        s++;
        d>>=1;
    }
    while(j < k)
    {
        ll x = rand()%(p-2) + 2;
        ll gcdD = gcd(x,p);
        if(gcdD > 1)
            return 0;
        x = powerMod(x,d,p);
        if(x == p-1 || x == 1)
            return 1;
        for(int r = 1; r < s; ++r)
        {
            x = ((x*x)^2)%p;
            if(x == p-1)
                return 1;
        }
        ++j;
    }
    return 0;
}



