//
// Created by Akgzulag on 11.03.2023.
//
#include <iostream>
#include <cmath>
#include <fstream>
#include "algorithms.h"
#include <gmpxx.h>
#include <chrono>
#include <map>

using std::cin, std::cout,std::ifstream;




bool factor(ll n, std::map<ll, int>& fac, const std::vector<ll> primes)
{
    ll q = 0;

    if(algo::MillerRabin(n))
    {
        fac[n]++;
        return 1;
    }

    while (true)
    {
        q = algo::trial(n);
        if (q == -1)
        {
            break;
        }
        n /= q;
        fac[q]++;
    }
    if (n == 1)
        return 1;

    if(algo::MillerRabin(n))
    {
        fac[n]++;
        return 1;
    }

    q = algo::pollard(n);
    if (!algo::MillerRabin(q))
    {
        factor(q,fac,primes);
    } else
    {
        fac[q]++;
    }

    n/=q;

    if(n == 1)
        return 1;

    if(algo::MillerRabin(n))
    {
        fac[n]++;
        return 1;
    }

    q = algo::methodBrillhartMorrison(n, primes);

    if(q == -1)
    {
        std::cout <<'\n'<<"can't factor n";
        return 0;
    }

    if(!algo::MillerRabin(q))
    {
        factor(q,fac,primes);
    } else
    {
        fac[q]++;
    }

    n /= q;

    if(algo::MillerRabin(n))
    {
        fac[n]++;
        return 1;
    }else
    {
        factor(n,fac,primes);
    }

}

int main()
{


    const char* primeNumbersFile = std::getenv("PRIME_NUMBERS_FILE");
    ifstream infile1("../firstMilionPrimeNumbers.txt"); // відкриваємо файл для зчитування
    ifstream infile2(primeNumbersFile); // відкриваємо файл для зчитування

    std::vector<ll> primes;
    if(infile1.is_open())
    {
        long long p;
        while (infile1 >> p)
        {
            primes.push_back(p);
        }
        infile1.close();
    }else if (infile2.is_open())
    {
        long long p;
        while (infile1 >> p)
        {
            primes.push_back(p);
        }
        infile1.close();
    } else
    {
        std::cout<<"can't open file with prime numbers";
        return 0;
    }

    std::map<ll,int> fac;

    ll n;

    cin>>n;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    factor(n,fac,primes);

    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    std::cout << "Час виконання алгоритму факторизації: " << duration.count() << " секунд" << std::endl;

    for(auto f: fac)
    {
        std::cout<<"("<<f.first<<")^"<<f.second<<" * ";
    }

}

//int main()
//{
//    auto start = std::chrono::high_resolution_clock::now();
//    auto end = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> duration = end - start;
//    long long n ;
//    cin>>n;
//    //n= 3009182572376191;
//    ll q;
//
//    start = std::chrono::high_resolution_clock::now();
//    if(algo::MillerRabin(n))
//    {
//        cout<<n<<"- просте \n ";
//        end = std::chrono::high_resolution_clock::now();
//        duration = end - start;
//
//        std::cout << "Час виконання Мілера рабіна на числі "<<n<<":"<< duration.count() << " секунд\n" << std::endl;
//        return 0;
//    }
//    end = std::chrono::high_resolution_clock::now();
//    duration = end - start;
//    std::cout << "Час виконання Мілера рабіна на числі "<<n<<": "<< duration.count() << " секунд\n" << std::endl;
//
//    q = algo::trial(n);
//
//    while (q != -1)
//    {
//        cout<<"Вивід пробного ділення:"<<q<<'\n';
//        n /= q;
//        q = algo::trial(n);
//    }
//    if( n== 1)
//        return 0;
//
//    start = std::chrono::high_resolution_clock::now();
//    if(algo::MillerRabin(n))
//    {
//        cout<<n<<"- просте \n ";
//        end = std::chrono::high_resolution_clock::now();
//        duration = end - start;
//
//        std::cout << "Час виконання Мілера рабіна на числі "<<n<<":"<< duration.count() << " секунд\n" << std::endl;
//        return 0;
//    }
//    end = std::chrono::high_resolution_clock::now();
//    duration = end - start;
//    std::cout << "Час виконання Мілера рабіна на числі "<<n<<":"<< duration.count() << " секунд\n" << std::endl;
//
//    start = std::chrono::high_resolution_clock::now();
//    q = algo::pollard(n);
//    cout<<"Вивід полард: "<<q<<'\n';
//
//    n/=q;
//
//    end = std::chrono::high_resolution_clock::now();
//    duration = end - start;
//
//    std::cout << "Час виконання Поларда: " << duration.count() << " секунд" << std::endl;
//
//
//    const char* primeNumbersFile = std::getenv("PRIME_NUMBERS_FILE");
//
//    ifstream infile("../firstMilionPrimeNumbers.txt"); // відкриваємо файл для зчитування
//    //ifstream infile(primeNumbersFile); // відкриваємо файл для зчитування
//
//
//    if(!infile.is_open())
//    {
//        std::cout<<"file can't open\n";
//        return 0;
//    }
//
//    std::vector<ll> primes;
//    long long p;
//    while (infile >> p)
//    {
//        primes.push_back(p);
//    }
//    infile.close();
//
//
//    start = std::chrono::high_resolution_clock::now();
//    if(algo::MillerRabin(n))
//    {
//        cout<<n<<"- просте \n ";
//        end = std::chrono::high_resolution_clock::now();
//        duration = end - start;
//
//        std::cout << "Час виконання Мілера рабіна на числі "<<n<<":"<< duration.count() << " секунд\n" << std::endl;
//        return 0;
//    }
//    end = std::chrono::high_resolution_clock::now();
//    duration = end - start;
//    std::cout << "Час виконання Мілера рабіна на числі "<<n<<":"<< duration.count() << " секунд\n" << std::endl;
//
//    while(true)
//    {
//        ll q = algo::methodBrillhartMorrison(n, primes);
//        if(q == -1)
//        {
//                std::cout <<'\n'<<"can't factor n";
//                return 0;
//        }
//        std::cout<<q<<"\n";
//        n /= q;
//        start = std::chrono::high_resolution_clock::now();
//        if(algo::MillerRabin(n))
//        {
//            cout<<n<<"- просте \n ";
//            end = std::chrono::high_resolution_clock::now();
//            duration = end - start;
//
//            std::cout << "Час виконання Мілера рабіна на числі "<<n<<":"<< duration.count() << " секунд\n" << std::endl;
//            return 0;
//        }
//        end = std::chrono::high_resolution_clock::now();
//        duration = end - start;
//        std::cout << "Час виконання Мілера рабіна на числі "<<n<<":"<< duration.count() << " секунд\n" << std::endl;
//    }
//
//    return 0;
//}