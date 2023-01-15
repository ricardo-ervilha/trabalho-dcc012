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
    void desalocar(NoB *no);
    int compInsercao = 0;//contabilizar as comparacoes de chave na inserçao
    int tempoInsercao = 0;
    int compBusca = 0;//contabilizar as comparacoes de chave na busca
    int tempoBusca = 0;


public:
    ArvoreB();
    ~ArvoreB();
    ProductReview *busca(string userId, string productId);
    void insere(ProductReview *pr);
    void print();
    
    int getCompInsercao();
    void setCompInsercao(int val);

    int getCompBusca();
    void setCompBusca(int val);
};

#endif