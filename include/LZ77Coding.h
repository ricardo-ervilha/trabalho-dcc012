#ifndef LZ77_H
#define LZ77_H
#include "ProductReview.h"
#include <iostream>
#include <cstring>

using namespace std;

typedef struct{
   

}LZ77List;

class LZ77Coding{
    private:
        ProductReview *list;
        int registros;
        void LZ77Compress(ProductReview *list);
 
    public:   
        LZ77Coding();
        LZ77Coding(ProductReview *, int);
        ~LZ77Coding();
        void comprime();
        void imprime();
};

#endif