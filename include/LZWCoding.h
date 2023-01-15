#ifndef LZW_H
#define LZW_H
#include "ProductReview.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;



class LZWCoding{
    private:
        ProductReview *list;
        int registros;
        void LZWCompress(ProductReview *list);
        int InicializaDicionario(string dicionario[]);
    public:   
        LZWCoding();
        LZWCoding(ProductReview *, int);
        ~LZWCoding();
        string Comprime(string concatenada);
        string Descomprime(string codigo);
        
};

#endif