//
// Created by Akgzulag on 11.03.2023.
//
#include <iostream>
#include <cmath>
#include <fstream>
#include "algorithms.h"

using std::cin, std::cout,std::ifstream;

int main()
{
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
    long long n = 7442109405582674149;
    std::cout <<'\n'<<algo::methodBrillhartMorrison(n, primes);


    double alpha = 1 / sqrt(2);
   // cout << pow(exp(sqrt(log(n)*log(log(n)))), alpha);
    return 0;
}