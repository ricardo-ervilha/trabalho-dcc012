#ifndef HASHPRODUCT_H
#define HASHPRODUCT_H

#include "ProductReview.h"
#include "MergeSort.h"
#include "List.h"


typedef struct{
    string productId;
    int qtdReviews;

} RegistroHash;


class HashProduct{

private:
    int tam;
    RegistroHash *table;
    string path;

public:
    HashProduct(string path);
    ~HashProduct();
    void inicializa(int n);
    RegistroHash* createTable(int n);
    int converteStringInt(string productId);
    int funcaoHash(int val);
    void insere(ProductReview produto);
    bool busca();
    void sort();
    int contabilizaFrequencia();
    void printTable();
};

#endif