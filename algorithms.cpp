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
            while (x != 0)
            {
                while (x % 2 == 0)
                {
                    x /= 2;
                    int r = n % 8;
                    if (r == 3 || r == 5)
                        t = -t;
                }
                int temp = x;
                x = n;
                n = temp;
                if (x % 4 == 3 && n % 4 == 3)
                    t = -t;
                x %= n;
            }
            if (n == 1) return t;
            else return 0;
        }

        std::vector<ll> buildBase(const ll& n, std::vector<ll>& primes, const double& alpha)
        {
            long long L = pow(exp(sqrt(log2(n)*log2(log2(n)))), alpha);
            std::cout<<"L= "<<L<<'\n';
            std::vector<ll> base;
            base.push_back(-1);
            for(auto p : primes)
            {
                if(p > L) return base;
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
                b2[0] = b2[0] - n;
            for(int i = 1; i < k; ++i)
            {
                v[i % 2] = (n - u[(i-1) % 2] * u[(i - 1) % 2])/v[(i - 1) % 2];
                alpha = (sqrtN + (double)u[(i - 1) % 2])/(double)v[i % 2];
                a[i % 2] = (ll)alpha;
                u[i % 2] = a[i % 2] * v[i % 2] - u[(i - 1) % 2];
                if(i == 1)
                {
                    b[i] = (a[i % 2]*b[i-1] + 1) % n;
                } else
                {
                    b[i] = (a[i % 2]*b[i-1] + b[i-2]) % n;
                }

                b2[i] = (b[i]*b[i])%n;
                if(b2[i] > n - b2[i])
                    b2[i] = b2[i] - n;
            }
            return std::pair<std::vector<ll>,std::vector<ll>>(b,b2);
        }

        bool factorB(ll x, const std::vector<ll>& base, std::vector<int>& v)
        {
            if(x < 0)
            {
                v[0] = 1;
                x *= -1;
            }
            for(int i = 1; i < base.size(); ++i)
            {
                while(x % base[i] == 0)
                {
                    v[i] ^= 1;
                    x /= base[i];
                }
                if(x == 1)
                    return 1;
            }
            return 0;
        }

        std::vector<std::vector<int>> createSystem(const std::vector<ll> b2, const std::vector<ll>& base, std::vector<int>& index)
        {
            std::vector<std::vector<int>> sys;
            for (int i = 0; i < b2.size(); ++i)
            {
                std::vector<int> v(base.size(), 0);
                if(factorB(b2[i], base, v))
                {
                    sys.push_back(v);
                    index.push_back(i);
                }
            }
            return sys;
        }

        void addColumn(int j, int k, std::vector<std::vector<int>>& system)
        {
            for(int i = 0; i < system.size(); ++i)
            {
                system[i][k] ^= system[i][j];
            }
        }

        std::vector<int> solveSystem(std::vector<std::vector<int>>& system)
        {
            std::vector<ll> result(system.size());
            std::vector<int> flag(system.size());
            for(int i = 0; i < system.size(); ++i)
                flag[i] = 0;

            for(int j = 0; j < system[0].size(); ++j)
            {
                int i = -1;
                for(int x = 0; x < system.size(); ++x)
                    if(system[x][j] == 1)
                        i = x;
                if(i != -1)
                    for(int k = 0; k < system[0].size(); ++k)
                    {
                        flag[i] = 1;
                        //std::cout<<'i'<<i<<'\n';
                        if(k != j && system[i][k]==1)
                        {
                            addColumn(j,k,system);
//                            std::cout<<"A"<<j<<"to"<<k<<'\n';
//                            for (int n = 0; n < system.size(); ++n) {
//                                for (int m = 0; m < system[0].size(); ++m) {
//                                    std::cout << system[n][m] << " ";
//                                }
//                                std::cout << '\n';
//                            }
                        }
                    }
            }

//            for (int i = 0; i < system.size(); ++i)
//
//            std::cout<<'\n';
//            for (int i = 0; i < system.size(); ++i)
//            {
//                std::cout<<flag[i]<<"    ";
//                for (int j = 0; j < system[0].size(); ++j)
//                {
//                    std::cout<< system[i][j] << " ";
//                }
//                std::cout<<'\n';
//            }
            return flag;
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
    n = 9073;
    double alpha = 1/sqrt(2);

    std::vector base = buildBase(n,primes,alpha);
//    std::vector<ll> base;
//    base.push_back(-1);base.push_back(2);base.push_back(3);base.push_back(7);
    std::cout<<base.size()<<'\n';
    for(auto i: base)
        std::cout << i<< ' ';
    std::cout<<"\n";
    std::vector<ll> b,b2;

    auto t = continuedFraction(n,base.size()+1);
    for(int i = 0; i < t.second.size(); ++i)
    {
        std::cout<<t.second[i]<<" ";
    }
    std::cout<<"\n";

    b = t.first;
    b2 = t.second;
    std::vector<int> index;
    auto system = createSystem(b2, base, index);
    for (int i = 0; i < system.size(); ++i)
    {
        std::cout << index[i]<<' ';
        for (int j = 0; j < system[0].size(); ++j)
        {
            std::cout<< system[i][j]<<' ';
        }
        std::cout<<"\n";
    }

    std::vector<std::vector<int>> system2;



    auto flag = algo::solveSystem(system);
    std::vector<int> resultIndex;
    std::cout<<'\n';
            for (int i = 0; i < system.size(); ++i)
            {
                std::cout<<i<<' '<<flag[i]<<"    ";
                for (int j = 0; j < system[0].size(); ++j)
                {
                    std::cout<< system[i][j] << " ";
                }
                std::cout<<'\n';
            }
//    flag[0] = -1;
    ll r1 =0, r2 =0;
    for(int k = 0; k < flag.size(); ++k)
    {
        if(flag[k] == 0)
        {
            resultIndex.push_back(index[k]);
            for (int j = 0; j < system[k].size(); ++j)
            {
                if(system[k][j])
                    for (int i = 0; i < system.size(); ++i)
                    {
                        if (flag[i] == 1 && system[i][j] && i != k)
                        {
                            resultIndex.push_back(index[i]);
                            break;
                        }
                    }
            }
            ll X=1,Y=1;
            std::cout<<'\n';
            for(auto id: resultIndex)
            {
                X *= b[id];
                Y *= b2[id];
                std::cout<<id<<' '<<b[id]<<" "<<b2[id]<<'\n';
            }
            Y = sqrt(Y);
            r1 = gcd(abs(X + Y), n);
            r2 = gcd(abs(X - Y), n);
            std::cout<<gcd((X-Y)%n,n)<<' '<<gcd((X-Y)%n,n)<<'\n';
            if(r1 != 1 && r1 != n)
                return r1;
            if (r2 != 1 && r2 != n)
                return r2;
            else
                continue;
        }
    }



//    for (int i = 0; i < resultIndex.size(); ++i)
//    {
//        std::cout<<resultIndex[i]<<' ';
//    }




}



