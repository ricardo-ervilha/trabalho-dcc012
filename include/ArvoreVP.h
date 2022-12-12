#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"
#include "ProductReview.h"

class ArvoreVP{

private:
    NoVP * raiz;
    int n; //Quantidade de nós
    string concat(string s1, string s2); //Concatena userId e productId
    NoVP* rotSimplesEsq(NoVP *p);
    NoVP* rotSimplesDir(NoVP *p);
    NoVP* recolor(NoVP *p);
    NoVP* libera(NoVP *p);
    NoVP* auxInsere(NoVP* p, string info);
    ProductReview* auxBusca(NoVP *p, string info);
    void auxPrint(NoVP *p);

public:
    ArvoreVP();
    ~ArvoreVP();
    bool vazia(); //Verifica se a árvore está vazia
    void insere(ProductReview *pr);
    ProductReview* busca(string userId, string productId);
    void print();
};

#endif