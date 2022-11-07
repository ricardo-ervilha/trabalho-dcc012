#ifndef BUCKETSORT_H
#define BUCKETSORT_H
#include "ProductReview.h"
#include "ListaEncad.h"

using namespace std;

class BucketSort
{
private:
    ProductReview *list;
    int registros;
    ListaEncad **buckets;
    ListaEncad *listaOrdenada;

public:
    BucketSort();
    BucketSort(ProductReview *, int);
    ~BucketSort();
    void sort();
    void ordena();
    void imprime();
    void insertionSort(int);
    void mergeSort(int);
    void concatBucket(int);
};

#endif