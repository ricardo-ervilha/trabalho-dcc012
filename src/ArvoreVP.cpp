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
    string info = concat(pr->getUserId(),pr->getProductId());
    raiz = auxInsere(raiz, info);
}

NoVP *ArvoreVP::auxInsere(NoVP* p, string info)
{
    bool correcao = false;

    if(p == NULL){
        p = new NoVP();
        p->setInfo(info);
        if(p == raiz)
            p->setColor() = false;
        p->setEsq(NULL);
        p->setDir(NULL);
    }

    else if(info < p->getInfo())
        {
            p->setEsq(auxInsere(p->getEsq(), info));
            p->getEsq()->setPai(p);
            if(p != raiz){
                if(p->getColor() == true && p->getEsq()->getColor() == true)
                    correcao = true;
            }
        }
    else
        {
            p->setDir(auxInsere(p->getDir(), info));
            p->getDir()->setPai(p);
            if(p != raiz){
                if(p->getColor() == true && p->getDir()->getColor() == true)
                    correcao = true;
            }
        }

    if(correcao){
        if(p->getPai()->getPai()->getDir()->getColor() == true) //pai e tio (direito) vermelhos
        {
            recolor(p->getPai()->getPai());
            recolor(p->getPai());
            recolor(p->getPai()->getPai()->getDir());

            if(p->getPai()->getPai() == raiz)
                p->getPai()->getPai()->setColor() = false;
        }

        else if(p->getPai()->getPai()->getEsq()->getColor() == true) //pai e tio (esquerdo) vermelhos
        {
            recolor(p->getPai()->getPai());
            recolor(p->getPai());
            recolor(p->getPai()->getPai()->getEsq());

            if(p->getPai()->getPai() == raiz)
                p->getPai()->getPai()->setColor() = false;
        }

        else if(p->getPai()->getPai()->getDir()->getColor() == false || p->getPai()->getPai()->getDir() == NULL){
        //pai vermelho e tio (direito) preto ou nulo

        if(p->getPai() == p->getPai()->getEsq()){
            rotSimplesDir(p->getPai());
            recolor(p->getPai())
            recolor(p->getPai()->getPai())
            if(p->getPai() == raiz)
                p->getPai()->setColor() = false;
        }
        else
            {
                //rotacao dupla para a direita
                 rotSimplesEsq(p);
                 rotSimplesDir(p);
                 recolor(p)
                 recolor(p->getPai()->getPai())
                 if(p == raiz)
                    p->setColor() = false;
            }

        }

        else if(p->getPai()->getPai()->getEsq()->getColor() == false || p->getPai()->getPai()->getEsq() == NULL){
        //pai vermelho e tio (esquerdo) preto ou nulo

        if(p->getPai() == p->getPai()->getDir())
        {
            rotSimplesEsq(p->getPai());
            recolor(p->getPai())
            recolor(p->getPai()->getPai())
            if(p->getPai() == raiz)
                p->getPai()->setColor() = false;
        }
        else
            {
                //rotacao dupla para a esquerda
                 rotSimplesDir(p);
                 rotSimplesEsq(p);
                 recolor(p)
                 recolor(p->getPai()->getPai())
                 if(p == raiz)
                    p->setColor() = false;
            }

        }

        correcao = false;

    }

    return p;
}

void ArvoreVP::recolor(NoVP* p){
    if(p->getColor() == false)
        p->setColor() == true;
    else
        p->setColor() == false;
}

string ArvoreVP::concat(string s1, string s2){
    return s1+s2;
}

void ArvoreVP::rotSimplesEsq(NoVP* r){
    q = r->getDir();
    r->setDir() = q->getEsq();
    q->setEsq() = r;
}

void ArvoreVP::rotSimplesDir(NoVP* r){
    q = r->getEsq();
    r->setEsq() = q->getDir();
    q->setDir() = r;
}

ProductReview *ArvoreVP::busca(string userId, string productId)
{

}

void ArvoreVP::print()
{
}