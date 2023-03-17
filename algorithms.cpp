#include "algorithms.h"

namespace algo
{
    namespace
    {
        ll count(ll n)
        {
            int count = 0;
            while(n != 0)
            {
                n=n/10;
                count++;
            }
            return count;
        }

        ll digit(ll a, int position)
        {
            for (int i = 0; i < position; i++){
                a=a/10;
            }
            a=a%10;
            return a;
        }

        ll find_r(ll mod, ll position)
        {
            ll r = 1;
            for(int i=0; i < position; i++)
            {
                r = (r*10)%mod;
            }
            return r;
        }
        ll function(long long x, ll mod)
        {
            return (x*x+1)%mod;
        }

        ll gcd(long long a, long long b)
        {
            ll d = 1;
            while (d!=0)
            {
                d=a%b;
                a=b;
                b=d;
            }
            return a;
        }

        ll powerMod(ll x, ll pow,ll mod)
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

        int jacobi(ll x, ll n)
        {
            int t = 1;
            while (x != 0) {
                while (x % 2 == 0) {
                    x /= 2;
                    int r = n % 8;
                    if (r == 3 || r == 5) t = -t;
                }
                int temp = x;
                x = n;
                n = temp;
                if (x % 4 == 3 && n % 4 == 3) t = -t;
                x %= n;
            }
            if (n == 1) return t;
            else return 0;
        }

        std::vector<ll> buildBase(const ll& n, std::vector<ll>& primes, const double& alpha)
        {
            long long L = pow(exp(sqrt(log(n)*log(log(n)))), alpha);

            std::vector<ll> base;
            base.push_back(-1);
            for(auto p : primes)
            {
                if(jacobi(n,p) == 1)
                    base.push_back(p);
            }

            return base;
        }

        std::pair<std::vector<ll>,std::vector<ll>> continuedFraction(ll n,int k)
        {
            ll v[2],a[2],u[2];
            v[0] = 1;
            a[0] = (ll)sqrt(n);
            u[0] = a[0];
            double alpha,sqrtN = sqrt(n);
            std::vector<ll> b(k);
            std::vector<ll> b2(k);
            b[0] = a[0];
            b2[0] = (b[0]*b[0])%n;
            if(b2[0] > n - b2[0])
                b2[0] = n- b2[0];
            for(int i = 1; i < k; ++i)
            {
                v[i % 2] = (n - u[(i-1) % 2 ] * u[(i - 1) % 2]);
                alpha = (sqrtN + u[(i - 1) % 2])/v[i % 2];
                a[i % 2] = (ll)alpha;
                u[i % 2] = a[i % 2] * v[i % 2] - u[(i - 1) % 2];
                if(i == 1)
                {
                    b[i] = a[i]*b[i-1] + 1;
                } else
                {
                    b[i] = a[i]*b[i-1] + b[i-2];
                }
                b[i] = (b[i]*b[i]) % n;
                b2[i] = (b[i]*b[i])%n;
                if(b2[i] > n - b2[i])
                    b2[i] = n- b2[i];
            }
            return std::pair<std::vector<ll>,std::vector<ll>>(b,b2);
        }

        std::vector<ll> factorB(ll x, const std::vector<ll>& base)
        {
            std::vector v(base.size(),0);
            while (x != 1)
            {
                if(x < 0)
                {
                    v[0] = 1;
                    x *= -1;
                }
                for(int i = 1; i < base.size(); ++i)
                {
                    int k = 0;
                    while(x % base[i] == 0)
                    {
                        x/=base[i];
                        ++k;
                    }
                    v[i] = k%2;
                }
            }
        }

        std::vector<std::vector<ll>> createSystem(const std::vector<ll> b2,const std::vector<ll>& base)
        {
            std::vector<std::vector<ll>> sys;
            for(auto i: b2)
            {
                sys.push_back(factorB(i,base));
            }
        }

    }
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

ll algo::pollard(long long n) {
    ll x = 1;
    ll y = 1;
    ll d = 1;
    while(d == 1){
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

ll algo::methodBrillhartMorrison(ll n, std::vector<ll> primes)
{
    double alpha = 1/sqrt(2);

    std::vector base = buildBase(n,primes,alpha);
    std::vector<ll> b,b2;

    auto t = continuedFraction(n,primes.size());
    b = t.first;
    b2 = t.second;

    //b = b + 1/(4*b);
}



