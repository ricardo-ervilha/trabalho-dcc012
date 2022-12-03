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
    if(raiz == NULL){
        raiz = new NoVP();
        raiz->setInfo(info);
        raiz->setEsq(NULL);
        raiz->setDir(NULL);
        raiz->setColor(false);
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

        if(p->getPai()->getDir() == p){
            if(p->getPai()->getEsq() != NULL || p->getPai()->getEsq()->getColor() == false)
            {
                //pai vermelho e tio (esquerdo) preto 
                if(p->getEsq() != NULL && p->getEsq()->getColor() == true){
                    //rotacao dupla para a esquerda(rl)
                    rotSimplesDir(p);
                    rotSimplesEsq(p->getPai());
                    recolor(p->getEsq());
                    recolor(p->getPai());
                    if (p->getEsq() == raiz)
                        p->getEsq()->setColor(false);
                }else if(p->getDir() != NULL && p->getDir()->getColor() == true){
                    rotSimplesEsq(p->getPai());
                    recolor(p);
                    recolor(p->getPai());
                    if (p == raiz)
                        p->setColor(false);
                }
            }  else {
                //Pai e tio (esquerdo) vermelho
            
                recolor(p);
                recolor(p->getPai()->getEsq());
            }
        }else{

           if(p->getPai()->getDir() != NULL || p->getPai()->getDir()->getColor() == false){
                //Pai vermelho e tio(direito) preto
                if(p->getEsq() != NULL && p->getEsq()->getColor() == true){
                    rotSimplesDir(p->getPai());
                    recolor(p);
                    recolor(p->getPai());
                    if (p == raiz)
                        p->setColor(false);
                }
                else if(p->getDir() != NULL && p->getDir()->getColor() == true)
                {
                    //Rotação dupla para a direita
                    rotSimplesEsq(p);
                    rotSimplesDir(p->getPai());
                    recolor(p->getDir());
                    recolor(p->getPai());
                    if (p->getDir() == raiz)
                        p->getDir()->setColor(false);
                }
           }else{
                //pai vermelho e tio(direito) vermelho

                recolor(p);
                recolor(p->getPai()->getDir());

                if (p->getPai() == raiz)
                    p->getPai()->setColor(false);
         
           }

        }
        correcao = false;

    }

    return p;
}

void ArvoreVP::recolor(NoVP* p){
    if(p->getColor() == false)
        p->setColor(true);
    else
        p->setColor(false);
}

string ArvoreVP::concat(string s1, string s2){
    return s1+s2;
}

void ArvoreVP::rotSimplesEsq(NoVP* r){
    NoVP *q = r->getDir();
    r->setDir(q->getEsq());
    q->setEsq(r);
}

void ArvoreVP::rotSimplesDir(NoVP* r){
    NoVP *q = r->getEsq();
    r->setEsq(q->getDir());
    q->setDir(r);
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