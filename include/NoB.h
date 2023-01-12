#ifndef NOB_H
#define NOB_h
#include <iostream>
#include <cmath>
#include "ProductReview.h"
using namespace std;

struct
{
    int id;    // id único para a avaliação => userId + productId
    int indexLoc; // id único para sua localização no arquivo binário
} typedef Info;

class NoB
{
public:
    NoB(int ordem);
    ~NoB();

    Info *chaves;             // Array com capacidade para m-1 chaves
    NoB **filhos;                 // Array de ponteiros para os m filhos
    int n;                              // Contador do número de chaves presentes no nó
    int ordem;              //número máximo de filhos permitidos no nó
    bool ehFolha = true;                // Indica se o nó é folha ou não
    
    bool cheio() { return n == ordem-1; } // verificar se encheu o vetor de chaves

    NoB *cisao(Info);//divide os valores entre o no atual e um novo no criado. retorna o novo nó criado
    NoB inserir(Info);//inserir chave de forma ordenada
    void printKey(int);
    void printKeys();

};

#endif