#ifndef ARVOREB_H
#define ARVOREB_H

#include "NoB.h"
#include "ProductReview.h"
#include "File.h"

class ArvoreB
{

private:
    NoB *raiz;
    int ordem;
    ProductReview *auxBusca(string K, NoB *no);
    NoB *encontrarFolha(string keySearch);
    void auxPrint(NoB *);
    NoB * search(NoB *x, Info *k);
    void splitChild(NoB *x, int i);
    void insert(ArvoreB *T, Info k);
    void insertNonFull(NoB *x, Info k);

public:
    ArvoreB();
    ~ArvoreB();
    ProductReview *busca(string userId, string productId);
    void insere(ProductReview *pr);
    void print();
};

#endif