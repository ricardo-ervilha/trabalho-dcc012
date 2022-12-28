#ifndef NOB_H
#define NOB_h
#include <iostream>
#include <cmath>
#include "ProductReview.h"
#define ORDEM 20
using namespace std;

struct
{
    string id;    // id único para a avaliação => userId + productId
    int indexLoc; // id único para sua localização no arquivo binário
} typedef Info;

class NoB
{
public:
    NoB();
    ~NoB();

    Info chaves[ORDEM - 1];             // Array com capacidade para m-1 chaves
    NoB *filhos[ORDEM];                 // Array de ponteiros para os m filhos
    int n;                              // Contador do número de chaves presentes no nó
    bool ehFolha = true;                // Indica se o nó é folha ou não
    
    bool cheio() { return n == ORDEM; } // verificar se encheu o vetor de chaves

    NoB *cisao(Info);//divide os valores entre o no atual e um novo no criado. retorna o novo nó criado
    NoB inserir(Info);//inserir chave de forma ordenada
};

#endif