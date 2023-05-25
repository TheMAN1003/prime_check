#include "algorithms.h"
#include <chrono>
#include <omp.h>
#include <map>
#include <fstream>

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
                    C = (C%mod * x%mod)%mod;
                }
                if(i != 0)
                    C = (C%mod * C%mod)%mod;
            }
            return C;
        }

        ll jacobi(ll x, ll n)
        {
            //std::cout<<x<<"|"<<n<<" "<<algo::powerMod(x,(n-1)/2,n)<<'\n';
            return algo::powerMod(x,(n-1)/2,n);
//            int t = 1;
//            while (x != 0)
//            {
//                while (x % 2 == 0)
//                {
//                    x /= 2;
//                    int r = n % 8;
//                    if (r == 3 || r == 5)
//                        t = -t;
//                }
//                int temp = x;
//                x = n;
//                n = temp;
//                if (x % 4 == 3 && n % 4 == 3)
//                    t = -t;
//                x %= n;
//            }
//            if (n == 1) return t;
//            else return 0;
        }

        std::vector<ll> buildBase(const ll& n, std::vector<ll>& primes, const double& alpha)
        {
            long long L = pow(exp(sqrt(log2(n)*log2(log2(n)))), alpha);
            std::cout<<"L= "<<L<<'\n';
           //L = 10004581;
           // L = 10000;
            //L = 1485;
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
            b2[0] = (b[0]%n*b[0]%n)%n;
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
                    b[i] = ((a[i % 2]%n)*(b[i-1]%n) + b[i-2]) % n;
                }

                mpz_class mod_result;  // Результат за модулем n
                mpz_class result;  // Результат піднесення до квадрату
                mpz_t tmpb;
                mpz_init_set_ui(tmpb, b[i]);

                // Піднесення a до квадрату
                mpz_pow_ui(result.get_mpz_t(), tmpb, 2);

                mpz_mod_ui(mod_result.get_mpz_t(), result.get_mpz_t(), n);

                b2[i] = (ll)mpz_get_ui(mod_result.get_mpz_t());
                if(b2[i] > n - b2[i])
                    b2[i] = b2[i] - n;
            }
            return std::pair<std::vector<ll>,std::vector<ll>>(b,b2);
        }

        bool binarySearch(ll prime, const std::vector<ll>& base)
        {
            int left = 0;
            int right = base.size() - 1;

            while (left <= right)
            {
                int mid = left + (right - left) / 2;

                if (base[mid] == prime)
                {
                    return true;
                }
                else if (base[mid] < prime)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }

            return false;
        }

        bool factorB(ll x, const std::vector<ll>& base, std::vector<int>& v, const std::vector<ll>& primes)
        {
            if(x < 0)
            {
                v[0] = 1;
                x *= -1;
            }
            std::vector<ll> checkBase;
            for(int i = 1; i < primes.size(); ++i)
            {
                if(x % primes[i] == 0)
                {
                    if(binarySearch(primes[i], base))
                    {
                        while(x % primes[i] == 0)
                        {
                            v[i] ^= 1;
                            x /= primes[i];
                        }
                        if(x == 1)
                        {
                            return 1;
                        }
                    } else
                        return 0;
                }
            }
            return 0;
        }

        bool factorB1(ll x, const std::vector<ll>& base, std::vector<int>& v, const std::vector<ll>& primes, std::vector<std::map<ll,int>>& b2factor , int k)
        {
            if(x < 0)
            {
                v[0] = 1;
                x *= -1;
                b2factor[k][-1] = 1;
            }
            for(int i = 1; i < base.size(); ++i)
            {
                while(x % base[i] == 0)
                {
                    b2factor[k][base[i]] += 1;
                    v[i] ^= 1;
                    x /= base[i];
                }
                if(x == 1)
                    return 1;
            }
            return 0;
        }

        std::vector<std::pair<int,std::vector<int>>> createSystem(const std::vector<ll> b2,std::vector<std::map<ll,int>>& b2factor ,const std::vector<ll>& base, std::vector<int>& index, const std::vector<ll> primes)
        {
            std::vector<std::pair<int,std::vector<int>>> sys;
            auto start = std::chrono::high_resolution_clock::now();


            for (int i = 0; i < b2.size(); ++i)
            {
                    std::vector<int> v (base.size(), 0);

                    if(factorB1(b2[i], base, v, primes, b2factor, i))
                    {

                        std::cout<<i<<"b2 = "<<b2[i]<<" "<<b2.size()<<"  "<<sys.size()<<'\n';

                        sys.push_back(std::make_pair(i,v));
                        //index.push_back(i);
                    }

                }


            auto end = std::chrono::high_resolution_clock::now();
            int s;
            //std::cin>>s;
            std::chrono::duration<double> duration = end - start;
            std::cout << "Час виконання: " << duration.count() << " секунд" << std::endl;
            int k;
            //std::cin>>k;
            return sys;
        }

        void addColumn(int j, int k, std::vector<std::pair<int,std::vector<int>>>& system)
        {
            for(int i = 0; i < system.size(); ++i)
            {
                system[i].second[k] ^= system[i].second[j];
            }
        }

        std::vector<int> solveSystem(std::vector<std::pair<int,std::vector<int>>>& system)//check
        {
            std::vector<ll> result(system.size());
            std::vector<int> flag(system.size());
            for(int i = 0; i < system.size(); ++i)
                flag[i] = 0;

            for(int j = 0; j < system[0].second.size(); ++j)
            {
                int i = -1;
                for(int x = 0; x < system.size(); ++x)
                    if(system[x].second[j] == 1)
                        i = x;
                if(i != -1)
                    for(int k = 0; k < system[0].second.size(); ++k)
                    {
                        flag[i] = 1;

                        if(k != j && system[i].second[k]==1)
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
    //std::cout << "Trial method was unsuccessful\n" ;
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

std::string algo::methodBrillhartMorrison(ll n, std::vector<ll> primes)
{
    auto start = std::chrono::high_resolution_clock::now();
    double alpha = 1/sqrt(2) ;
    std::cout<<alpha<<'\n';
    std::vector<ll> base = buildBase(n,primes, alpha);
    std::vector<ll> b,b2;
    auto t = continuedFraction(n,base.size());

    b = t.first;
    b2 = t.second;

    std::vector<int> index;
    std::vector<std::map<ll,int>> b2factor(b2.size());
    auto system = createSystem(b2,b2factor, base, index, primes);

    std::vector<std::vector<int>> s;
    for(int i = 0; i < system.size(); ++i)
    {
        std::vector<int> tmp;
        for(int j = 0; j < system[i].second.size();++j)
        {
            tmp.push_back(system[i].second[j]);
        }
        s.push_back(tmp);
    }

    auto flag = algo::solveSystem(system);
    for (int i = 0; i < system.size(); ++i)
    {
        std::cout<< system[i].first<<' ';
        for (int j = 0; j < system[i].second.size(); ++j)
        {
            std::cout<< system[i].second[j]<<' ';
        }
        std::cout<<"\n";
    }

    std::cout<<"\n";
    std::vector<int> resultIndex;

    for(int k = 0; k < flag.size(); ++k)//рядок
    {
        if(flag[k] == 0) // шукаємо по 1 його залежні
        {
            std::cout<<"k="<<k<<'\n';
            resultIndex.push_back(system[k].first);
            for (int j = 0; j < system[k].second.size(); ++j)
            {
                if(system[k].second[j] == 1)
                {
                    for (int i = 0; i < system.size(); ++i)
                    {
                        if (flag[i] == 1 && system[i].second[j] == 1 && i != k)
                        {
                            resultIndex.push_back(system[i].first);
                            break;
                        }
                    }
                }

            }

            std::vector<int> a(system[0].second.size(),0);

            std::cout<<"\n";
            mpz_class X(1),Y(1);

            std::map<ll, int> factorY;
            for(auto id: resultIndex)
            {
                mpz_mul_ui(X.get_mpz_t(), X.get_mpz_t(), b[id]);

                mpz_mul_ui(Y.get_mpz_t(), Y.get_mpz_t(), abs(b2[id]));

                for(auto e: b2factor[id])
                {
                    factorY[e.first] += e.second;
                }

            }


            mpz_class Yr(1);
            for(auto e: factorY)
            {
                mpz_class result;
               // std::cout<<e.first<<"^"<<e.second<<'*'<<" ";
                if(e.first != -1)
                if(e.second % 2 ==0 )
                {
                    mpz_ui_pow_ui(result.get_mpz_t(), e.first, e.second/2);
                    Yr = Yr * result;
                }else
                {
                    return "BIG PROBLEM\n";
                }
            }
            //std::cout<<'\n';

           // std::cout<<"Y before sqrt "<<Y.get_str()<<'\n';
            mpz_class sqrtX = Y;
            Y = sqrt(Y);
            if(Y == Yr)
            {
                std::cout<<"PEREMOHA\n";
            }else
            {
                std::cout<<Y.get_str()<<'\n'<<Yr.get_str()<<'\n';
                std::cout<<"NOTPEREMOHA\n";
            }
            if(sqrtX == Y*Y)
                std::cout<<"Y NORM\n";

            mpz_class r1,r2;
            mpz_t N;
            mpz_init(N);
            mpz_set_si(N, n);
            mpz_class tmp1, tmp2;
            tmp1 = X + Yr;
            tmp2 = X - Yr;
            //std::cout<<'\n\n';
           // std::cout<<X.get_str()<<" "<<Y.get_str()<<" "<<sqrtX.get_str()<<'\n';
            mpz_t xPlusY, xMinusY;
            mpz_init(xPlusY);
            mpz_init(xMinusY);
            mpz_set(xPlusY, tmp1.get_mpz_t());
            mpz_set(xMinusY, tmp2.get_mpz_t());

            mpz_gcd(r1.get_mpz_t(), xPlusY, N);
            mpz_gcd(r2.get_mpz_t(), xMinusY, N);


            std::string  r1S = r1.get_str();
            std::string  r2S = r2.get_str();
            //std::cout<<"\nX+y = "<<tmp1.get_str()<<"\nX-Y"<<tmp2.get_str()<<'\n';
            std::cout<<"\n"<<r1S<< " "<<r2S<<'\n';
            mpz_clear(xPlusY);
            mpz_clear(xMinusY);
            X = 1;
            Y = 1;
            if(r1S != "1" && r1S != std::to_string(n))
            {
                mpz_clear(N);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                std::cout << "Час виконання БМ: " << duration.count() << " секунд" << std::endl;
                return r1.get_str();
            }
            if (r2S != "1" && r2S != std::to_string(n))
            {
                mpz_clear(N);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                std::cout << "Час виконання БМ: " << duration.count() << " секунд" << std::endl;
                return r2.get_str();
            }
            else
                continue;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Час виконання БМ: " << duration.count() << " секунд" << std::endl;
    return "problem";


//    for (int i = 0; i < resultIndex.size(); ++i)
//    {
//        std::cout<<resultIndex[i]<<' ';
//    }




}



