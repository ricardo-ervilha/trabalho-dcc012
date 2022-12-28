#ifndef ARVOREB_H
#define ARVOREB_H

#include "NoB.h"
#include "ProductReview.h"

class ArvoreB
{

private:
    NoB *raiz;
    ProductReview *auxBusca(string K, NoB *no);
    NoB *encontrarFolha(string keySearch);

public:
    ArvoreB();
    ~ArvoreB();
    ProductReview *busca(string userId, string productId);
    void insere(ProductReview *pr);
    void print();
    bool vazia() { return raiz == NULL; } // Verifica se a árvore está vazia

    NoB * search(NoB *x, Info *k);
    void splitChild(NoB *x, int i);
    void insert(ArvoreB *T, Info k);
    void insertNonFull(NoB *x, Info k);
};

#endif