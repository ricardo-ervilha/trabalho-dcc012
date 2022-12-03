#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"
#include "ProductReview.h"

class ArvoreVP{

private:
    NoVP * raiz;
    int n; //Quantidade de nós
    string concat(string s1, string s2); //Concatena userId e productId
    void rotSimplesEsq(NoVP *p);
    void rotSimplesDir(NoVP *p);
    void balanceia(NoVP *p);
    void recolor(NoVP *p);
    NoVP* libera(NoVP *p);

public:
    ArvoreVP();
    ~ArvoreVP();
    bool vazia(); //Verifica se a árvore está vazia
    void insere(ProductReview *pr);
    ProductReview* busca(string userId, string productId);
    void print();
};

#endif