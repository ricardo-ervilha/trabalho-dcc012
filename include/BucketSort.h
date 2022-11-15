#ifndef BUCKETSORT_H
#define BUCKETSORT_H
#include "ProductReview.h"
#include "ListaEncadProductReview.h"

using namespace std;

class BucketSort
{
private:
    ProductReview *vet;
    int n;
    ListaEncadProductReview **buckets;
    ListaEncadProductReview *listaOrdenada;
    int *compMov; // Vetor onde a posição 0 conta o número de comparações e posição 1 conta o número de movimentações
    NoProductReview *ordenada;

public:
    BucketSort();
    BucketSort(ProductReview *, int);
    ~BucketSort();
    void sort();
    void printBuckets();
    void printVet();
    void putInBuckets();
    void insertionSort(int);
    void sortedInsert(NoProductReview *, int);
    int *getCompMov() { return compMov; };
};

#endif