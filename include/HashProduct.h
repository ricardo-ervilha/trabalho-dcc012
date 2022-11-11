// #ifndef HASHPRODUCT_H
// #define HASHPRODUCT_H

// #include "ProductReview.h"
// #include "MergeSort.h"
// #include "List.h"
// #include <fstream>

// typedef struct
// {
//     string productId;
//     int qtdReviews;

// } RegistroHash;

// class HashProduct
// {

// private:
//     int tam;
//     RegistroHash *table;
//     string path;

//     int *chavesGeradas; // arquivo para armazenar as chaves geradas
//     int lastIndex = 0;
//     ofstream arqChavesGeradas;
//     ofstream arqTabelaHash;

// public:
//     HashProduct(string path);
//     ~HashProduct();
//     void inicializa(int n);
//     RegistroHash *createTable(int n);
//     int converteStringInt(string productId);
//     int funcaoHash(int val);
//     void insere(ProductReview produto);
//     bool busca();
//     void sort();
//     int contabilizaFrequencia();
//     void printTable();
//     int h1(string productId);
//     int h2(string productId);
//     int h(string productId, int collisions);
//     int asciiValue(char c);
//     void insereProduto(ProductReview produto);
// };

// #endif


#ifndef HASHPRODUCT_H
#define HASHPRODUCT_H

#include "ProductReview.h"
#include "MergeSort.h"
#include "List.h"
#include <fstream>


typedef struct{
    string productId;
    int qtdReviews;

} RegistroHash;


class HashProduct{

private:
    int tam;
    RegistroHash *table;
    string path;
    ofstream arqTabelaHash;

public:
    HashProduct(string path);
    ~HashProduct();
    void inicializa(int n);
    RegistroHash* createTable(int n);
    int h1(string productId);
    int h2(string productId);
    int sondagemDupla(string productId, int i);
    bool insere(ProductReview produto);
    bool busca();
    void sort();
    int contabilizaFrequencia();
    void printTable();
};

#endif