#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"
#include "ProductReview.h"
#include "File.h"

class ArvoreVP{

private:
    NoVP* raiz;
    int n; //Quantidade de nós
    File* arq;
    string concat(string s1, string s2); //Concatena userId e productId
    NoVP* rotSimplesEsq(NoVP *p);
    NoVP* rotSimplesDir(NoVP *p);
    NoVP* recolor(NoVP *p);
    NoVP* libera(NoVP *p);
    NoVP* auxInsere(NoVP* p, string info, int local);
    ProductReview* auxBusca(NoVP *p, string info);
    void auxPrint(NoVP *p);

public:
    ArvoreVP(File* arq);
    ~ArvoreVP();
    bool vazia(); //Verifica se a árvore está vazia
    void insere(ProductReview *pr);
    ProductReview* busca(string userId, string productId);
    void print();
};

#endif