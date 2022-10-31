#ifndef BUCKETSORT_H
#define BUCKETSORT_H
#include "ProductReview.h"
using namespace std;

class BucketSort{
    private:
        ProductReview *list;
        int registros;
        
    public:
        BucketSort();
        BucketSort(ProductReview *, int);
        ~BucketSort();
        void sort();
        void imprime();
};

#endif