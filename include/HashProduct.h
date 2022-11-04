#ifndef HASHPRODUCT_H
#define HASHPRODUCT_H

#include "ProductReview.h"
#include "MergeSort.h"
#include "List.h"

class HashProduct{

private:
    int tam;
    ProductReview* table; 

public:
    HashProduct();
    ~HashProduct();
    ProductReview* createTable(int n);
    int converteStringInt(string productId);
    int funcaoHash(int val);
    void insere(ProductReview produto);
    bool busca();
    void sort();
    int contabilizaFrequencia();

    void printTable();
};



#endif