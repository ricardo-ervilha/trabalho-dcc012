#include <iostream>
#include <stdlib.h>
#include "ListaEncad.h"

using namespace std;

ListaEncad::ListaEncad()
{
    primeiro = NULL;
    ultimo = NULL;
    n = 0;
}

ListaEncad::~ListaEncad()
{
    No *p = primeiro;
    while (p != NULL)
    {
        No *aux = p->getProx();
        delete p;
        p = aux;
    }
}

bool ListaEncad::busca(string idProduto)
{
    No *p = primeiro;
    while (p != NULL)
    {
        No *aux = p->getProx();
        if (p->getInfo()->getProductId() == idProduto)
            return true;
        p = aux;
    }
    return false;
}

ProductReview* ListaEncad::get(int k)
{
    No *p = primeiro;
    int i = 0;
    while (i < k && p != NULL)
    {
        p = p->getProx();
        i++;
    }

    if (p == NULL)
    {
        cout << "ERRO: Indice Invalido(ListaEncad::get)" << endl;
        exit(1);
    }
    else
        return p->getInfo();
}

void ListaEncad::set(int k, ProductReview* avaliacao)
{
    No *p = primeiro;
    int i = 0;
    while (i < k && p != NULL)
    {
        p = p->getProx();
        i++;
    }

    if (p == NULL)
    {
        cout << "ERRO: Indice Invalido(ListaEncad::set)" << endl;
        exit(1);
    }
    else
    {
        p->setInfo(avaliacao);
    }
}

void ListaEncad::insereInicio(ProductReview* avaliacao)
{
    No *p = new No();
    p->setInfo(avaliacao);

    p->setProx(primeiro);
    primeiro = p;
    n++;

    if (n == 1)
        ultimo = p;
}

void ListaEncad::insereFinal(ProductReview* avaliacao)
{
    No *p = new No();
    p->setInfo(avaliacao);
    p->setProx(NULL);

    if (ultimo != NULL)
    {
        ultimo->setProx(p);
    }
    else
    {
        cout << "ERRO: Impossivel inserir no final, pois ponteiro ultimo eh NULL." << endl;
        exit(1);
    }
    ultimo = p;
    n++;

    if (n == 1)
        primeiro = p;
}

void ListaEncad::insere(ProductReview* avaliacao, int k)
{
    if (k == 0)
    {
        insereInicio(avaliacao);
    }
    else if (k == n)
    {
        insereFinal(avaliacao);
    }
    else
    {
        
        No *p = new No();
        p->setInfo(avaliacao);
        int i = 0;
        No *t = primeiro;
        No* aux;
        
        while (i < k && aux != NULL)
        {
            aux = t;
            t = t->getProx();
            
            i++;
        }
        
        aux->setProx(p);
        p->setProx(t);
        n++;
        
    }
}

void ListaEncad::removeInicio(){
    
    if(primeiro == NULL){
        cout << "ERRO: Remocao em lista vazia." << endl;
        exit(1);
    }
    else
    {
        No *aux = primeiro->getProx();
        delete primeiro;
        primeiro = aux;
        n--;
        if (n == 1)
            ultimo = primeiro;
    }
}

void ListaEncad::removeFinal(){
    if(primeiro == NULL){
        cout << "ERRO: Remocao em lista vazia." << endl;
        exit(1);
    }
    else{
        No *aux;
        for(aux = primeiro; aux->getProx()->getProx() != NULL; ){
            aux = aux->getProx();
        }
        delete ultimo;
        aux->setProx(NULL);
        ultimo = aux;
        n--;

        if(ultimo == primeiro)
            primeiro = ultimo;
    }
}

void ListaEncad::remove(int k)
{
    if(k == 0){
        removeInicio();
    }
    else if(k == n-1){
        removeFinal();
    }
    else{
        No *t = primeiro;
        No* aux;
        int i = 0;
        while (i < k && aux != NULL)
        {
            aux = t;
            t = t->getProx();
            
            i++;
        }
        //t sera o cara que quero remover
        //aux esta antes de t
        //fazer aux apontar para o cara da direita de t
        
        aux->setProx(t->getProx());
        delete t;
        n--;
    }
}

void ListaEncad::printList()
{
    No *p;
    cout << "_Lista Encadeada_" << endl;
    for (p = primeiro; p != NULL; p = p->getProx())
        p->getInfo()->print();

    cout << endl;
}