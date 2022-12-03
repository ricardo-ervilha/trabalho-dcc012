#include "ArvoreVP.h"

ArvoreVP::ArvoreVP()
{
    n = 0;
    raiz = NULL;
}
ArvoreVP::~ArvoreVP()
{
    libera(raiz);
}

NoVP* ArvoreVP::libera(NoVP* p){
    if(p != NULL){
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = NULL;
    }

    return p;
}

bool ArvoreVP::vazia()
{
    return (raiz == NULL);
}

void ArvoreVP::insere(ProductReview *pr)
{
}
ProductReview *ArvoreVP::busca(string userId, string productId)
{
}
void ArvoreVP::print()
{
}