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

//    mpz_class X=256,Y=1;
//    long long b = 256;
//    mpz_mul_ui(X.get_mpz_t(), X.get_mpz_t(), b);
//    X = sqrt(X);
//    cout << X.get_str() << std::endl;
//
//
//    mpz_t n;
//    mpz_init(n);
//    mpz_set_ui(n, 100);
//
//    mpz_t result;
//    mpz_init(result);
//    mpz_sqrt(result, n);
//
//    gmp_printf("sqrt(%Zd) = %Zd\n", n, result);
//
//    mpz_clear(n);
//    mpz_clear(result);



    ifstream infile("../firstMilionPrimeNumbers.txt"); // відкриваємо файл для зчитування

    if(!infile.is_open())
        std::cout<<"lox";
    std::vector<ll> primes;
    long long p;
    while (infile >> p)
    {
        primes.push_back(p);
    }
    infile.close();
    int i =0;
//    for(auto p: primes)
//        if(algo::MillerRabin(p) != 1)
//            std::cout<<p<<'\n';
//    std::cout<<i;
    long long n = 7442109405582674149/239353;

    std::cout <<'\n'<<algo::methodBrillhartMorrison(n, primes);


    double alpha = 2 / sqrt(2);
   // cout << pow(exp(sqrt(log(n)*log(log(n)))), alpha);
    return 0;
}