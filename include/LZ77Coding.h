#ifndef LZ77_H
#define LZ77_H
#include "ProductReview.h"
#include <iostream>
#include <cstring>

using namespace std;

class LZ77Coding{
    private:
        
        
    public:   
        LZ77Coding();
        ~LZ77Coding();
        string Descomprime(string codigo);
        string Comprime(string concatenada);
};

#endif