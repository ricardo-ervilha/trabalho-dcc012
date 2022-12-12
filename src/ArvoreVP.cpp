#include "ArvoreVP.h"

bool rotSimEsq = false;
bool rotSimDir = false;
bool rotDupEsq = false;
bool rotDupDir = false;

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
    n++;
    string info = concat(pr->getUserId(),pr->getProductId());
    if(raiz == NULL){
        raiz = new NoVP();
        raiz->setInfo(info);
        raiz->setEsq(NULL);
        raiz->setDir(NULL);
        raiz->setColor(false);
        raiz->setPai(NULL);
    }else{
        raiz = auxInsere(raiz, info);
    }
}

NoVP *ArvoreVP::auxInsere(NoVP* p, string info)
{
    bool correcao = false;

    if(p == NULL){
        p = new NoVP();
        p->setInfo(info);
        p->setEsq(NULL);
        p->setDir(NULL);
    }
    else if(info < p->getInfo())
        {
            p->setEsq(auxInsere(p->getEsq(), info));
            p->getEsq()->setPai(p);
            if(p != raiz){
                if(p->getColor() == true)
                    correcao = true;
            }
        }
    else
        {
            p->setDir(auxInsere(p->getDir(), info));
            p->getDir()->setPai(p);
            if(p != raiz){
                if(p->getColor() == true)
                    correcao = true;
            }
        }

    if(rotSimEsq){
        p = rotSimplesEsq(p); //realiza rotacao simples a esquerda
        
        //recolorir pai e avo
        p = recolor(p);
        p->setEsq(recolor(p->getEsq()));

        rotSimEsq = false;
    }

    else if(rotSimDir){
        p = rotSimplesDir(p); //realiza rotacao simples a direita

        //recolorir pai e avo
        p = recolor(p);
        p->setDir(recolor(p->getDir()));

        rotSimDir = false;

    }

    else if(rotDupEsq)
    {
        p->setDir(rotSimplesDir(p->getDir()));
        p->getDir()->setPai(p);
        p = rotSimplesEsq(p);

        //recolorir no e avo
        p = recolor(p);
        p->setEsq(recolor(p->getEsq()));

        rotDupEsq = false;
    }

    else if(rotDupDir)
    {
        p->setEsq(rotSimplesEsq(p->getEsq()));
        p->getEsq()->setPai(p);
        p = rotSimplesDir(p);

        //recolorir no e avo
        p = recolor(p);
        p->setDir(recolor(p->getDir()));

        rotDupDir = false;
    }

    if(correcao){
        if(p->getPai()->getDir() == p) //pai esta na direita
        {
            if(p->getPai()->getEsq() != NULL && p->getPai()->getEsq()->getColor() == true){
                //pai e tio (da esquerda) do no sao vermelhos
                p = recolor(p);
                p->getPai()->setEsq(recolor(p->getPai()->getEsq()));
                p->setPai(recolor(p->getPai()));

                if(p->getPai() == raiz)
                    p->getPai()->setColor(false);

            }

            else
            {
                //pai vermelho e tio (da esquerda) nulo (NIL) ou preto
                if(p->getDir() != NULL && p->getDir()->getColor() == true)
                {
                    //filho existe e esta na direita do pai
                    rotSimEsq = true;
                }

                else if(p->getEsq() != NULL && p->getEsq()->getColor() == true)
                {
                    //filho existe e esta na direita do pai
                    rotDupEsq = true;
                }

            }

        }

        else //pai esta na esquerda
        {
            if(p->getPai()->getDir() != NULL && p->getPai()->getDir()->getColor() == true){
                //pai e tio (da direita) do no sao vermelhos
                p = recolor(p);
                p->getPai()->setDir(recolor(p->getPai()->getDir()));
                p->setPai(recolor(p->getPai()));

                if(p->getPai() == raiz)
                    p->getPai()->setColor(false);

            }

            else if(p->getPai()->getDir() == NULL || p->getPai()->getDir()->getColor() == false)
            {
                //pai vermelho e tio (da direita) nulo (NIL) ou preto
                if(p->getEsq() != NULL && p->getEsq()->getColor() == true)
                {
                    //filho existe e esta na esquerda do pai
                    rotSimDir = true;
                }

                else if(p->getDir() != NULL && p->getDir()->getColor() == true)
                {
                    //filho existe e esta na direita do pai
                    rotDupDir = true;
                }

            }

        }
        correcao = false;
    }
    return p;
}

NoVP* ArvoreVP::recolor(NoVP* p){
    NoVP* corTrocada = p;
    if(corTrocada->getColor() == false)
        corTrocada->setColor(true);
    else
        corTrocada->setColor(false);
    
    return corTrocada;
}

string ArvoreVP::concat(string s1, string s2){
    return s1+s2;
}

NoVP* ArvoreVP::rotSimplesEsq(NoVP* r){
    NoVP *q = r->getDir();
    r->setDir(q->getEsq());
    q->setEsq(r);

    if(r == raiz)
        q->setPai(NULL);
    else
        q->setPai(r->getPai());

    if(r->getDir() != NULL){
        r->getDir()->setPai(r);
    }

    r->setPai(q);
    
    return q;
}

NoVP* ArvoreVP::rotSimplesDir(NoVP* r){
    NoVP *q = r->getEsq();
    r->setEsq(q->getDir());
    q->setDir(r);

    if(r == raiz)
        q->setPai(NULL);
    else
        q->setPai(r->getPai());

    if(r->getEsq() != NULL)
        r->getEsq()->setPai(r);

    r->setPai(q);
    
    return q;
}

// ProductReview *ArvoreVP::busca(string userId, string productId)
// {
//     return auxBusca(raiz, concat(userId, productId));
// }

// ProductReview* ArvoreVP::auxBusca(NoVP *p, string info){
//     if(p == NULL)
//         return NULL;
//     else if(info == p->getInfo())
//         return p;
//     else if(info < p->getInfo())
//         return auxBusca(p->getEsq(), info);
//     else
//         return auxBusca(p->getDir(), info);
// }

void ArvoreVP::print()
{
    auxPrint(raiz);
    cout << endl;
}

void ArvoreVP::auxPrint(NoVP *p){
    if(p != NULL){
        auxPrint(p->getEsq());

        if(p->getColor() == true){
            cout << "\033[0;31m";
            cout << p->getInfo() <<  " ";
            cout << "\033[0m";
        }else{
            cout << p->getInfo() <<  " ";
        }

        auxPrint(p->getDir());
    }
}