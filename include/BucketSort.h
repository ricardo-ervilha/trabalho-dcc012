#ifndef BUCKETSORT_H
#define BUCKETSORT_H
#include "ProductReview.h"
#include "ListaEncad.h"

using namespace std;

class BucketSort
{
private:
    ProductReview *vet;
    int n;
    ListaEncad **buckets;
    ListaEncad *listaOrdenada;

public:
    BucketSort();
    BucketSort(ProductReview *, int);
    ~BucketSort();
    void sort();
    void printBuckets();
    void insertionSort(int);
    void mergeSort(int);
    void concatBucket(int);
    void putInBuckets();
    void listToArray();
};

#endif