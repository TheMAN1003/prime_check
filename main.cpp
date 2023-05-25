//
// Created by Akgzulag on 11.03.2023.
//
#include <iostream>
#include <cmath>
#include <fstream>
#include "algorithms.h"
#include <gmpxx.h>

using std::cin, std::cout,std::ifstream;






int main()
{

    long long n = 2500744714570633849;
    //n= 3009182572376191;
    ll q;
    q = algo::trial(n);
    while (q != -1)
    {
        cout<<q<<' ';
        n /= q;
        q = algo::trial(n);
    }
    q = algo::pollard(n);
    cout<<q<<' ';
    n/=q;
    const char* primeNumbersFile = std::getenv("PRIME_NUMBERS_FILE");

    ifstream infile("../firstMilionPrimeNumbers.txt"); // відкриваємо файл для зчитування
    //ifstream infile(primeNumbersFile); // відкриваємо файл для зчитування

    if(!infile.is_open())
        std::cout<<"lox";
    std::vector<ll> primes;
    long long p;
    while (infile >> p)
    {
        primes.push_back(p);
    }
    infile.close();
    if(!algo::MillerRabin(n))
        std::cout <<'\n'<<"BM done"+algo::methodBrillhartMorrison(n, primes)<<"BM";
    else
        std::cout<<n<<'\n';

    double alpha = 2 / sqrt(2);
   // cout << pow(exp(sqrt(log(n)*log(log(n)))), alpha);
//    return 0;
}