#include <iostream>
#include <stdlib.h>
#include "ListaEncadProductReview.h"

using namespace std;

ListaEncadProductReview::ListaEncadProductReview()
{
    primeiro = NULL;
    ultimo = NULL;
    n = 0;
}

ListaEncadProductReview::~ListaEncadProductReview()
{
    NoProductReview *p = primeiro;
    while (p != NULL)
    {
        NoProductReview *aux = p->getProx();
        delete p;
        p = aux;
    }
}

bool ListaEncadProductReview::busca(string idProduto)
{
    NoProductReview *p = primeiro;
    while (p != NULL)
    {
        NoProductReview *aux = p->getProx();
        if (p->getInfo().getProductId() == idProduto)
            return true;
        p = aux;
    }
    return false;
}

ProductReview ListaEncadProductReview::get(int k)
{
    NoProductReview *p = primeiro;
    int i = 0;
    while (i < k && p != NULL)
    {
        p = p->getProx();
        i++;
    }

    if (p == NULL)
    {
        cout << "ERRO: Indice Invalido(ListaEncadProductReview::get)" << endl;
        exit(1);
    }
    else
        return p->getInfo();
}

void ListaEncadProductReview::set(int k, ProductReview avaliacao)
{
    NoProductReview *p = primeiro;
    int i = 0;
    while (i < k && p != NULL)
    {
        p = p->getProx();
        i++;
    }

    if (p == NULL)
    {
        cout << "ERRO: Indice Invalido(ListaEncadProductReview::set)" << endl;
        exit(1);
    }
    else
    {
        p->setInfo(avaliacao);
    }
}

void ListaEncadProductReview::insereInicio(ProductReview avaliacao)
{
    NoProductReview *p = new NoProductReview();
    p->setInfo(avaliacao);

    p->setProx(primeiro);
    primeiro = p;
    n++;

    if (n == 1)
        ultimo = p;
}

void ListaEncadProductReview::insereFinal(ProductReview avaliacao)
{
    if (n == 0)
    {
        insereInicio(avaliacao);
    }
    else
    {

        NoProductReview *p = new NoProductReview();
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
}

void ListaEncadProductReview::insereListaFinal(ListaEncadProductReview *lista)
{
    if (this->getSize() == 0)
    {
        this->primeiro = lista->primeiro;
        this->ultimo = lista->ultimo;
        this->n = lista->n;
    }
    else
    {
        this->ultimo->setProx(lista->primeiro);
        this->ultimo = lista->ultimo;
        this->n += lista->n;
    }
}

void ListaEncadProductReview::insere(ProductReview avaliacao, int k)
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
        NoProductReview *p = new NoProductReview();
        p->setInfo(avaliacao);
        int i = 0;
        NoProductReview *t = primeiro;
        NoProductReview *ant;

        while (i < k && t != NULL)
        {
            ant = t;
            t = t->getProx();

            i++;
        }

        ant->setProx(p);
        p->setProx(t);
        n++;
    }
}

void ListaEncadProductReview::removeInicio()
{

    if (primeiro == NULL)
    {
        cout << "ERRO: Remocao em lista vazia." << endl;
        exit(1);
    }
    else
    {
        NoProductReview *aux = primeiro->getProx();
        delete primeiro;
        primeiro = aux;
        n--;
        if (n == 1)
            ultimo = primeiro;
    }
}

void ListaEncadProductReview::removeFinal()
{
    if (primeiro == NULL)
    {
        cout << "ERRO: Remocao em lista vazia." << endl;
        exit(1);
    }
    else
    {
        NoProductReview *aux;
        for (aux = primeiro; aux->getProx()->getProx() != NULL;)
        {
            aux = aux->getProx();
        }
        delete ultimo;
        aux->setProx(NULL);
        ultimo = aux;
        n--;

        if (ultimo == primeiro)
            primeiro = ultimo;
    }
}

void ListaEncadProductReview::remove(int k)
{
    if (k == 0)
    {
        removeInicio();
    }
    else if (k == n - 1)
    {
        removeFinal();
    }
    else
    {
        NoProductReview *t = primeiro;
        NoProductReview *aux;
        int i = 0;
        while (i < k && aux != NULL)
        {
            aux = t;
            t = t->getProx();

            i++;
        }
        // t sera o cara que quero remover
        // aux esta antes de t
        // fazer aux apontar para o cara da direita de t

        aux->setProx(t->getProx());
        delete t;
        n--;
    }
}

void ListaEncadProductReview::printList()
{
    NoProductReview *p;
    // cout << "_Lista Encadeada_" << endl;
    for (p = primeiro; p != NULL; p = p->getProx())
    {
        p->getInfo().print();
    }

    cout << endl;
}

int ListaEncadProductReview::getSize()
{
    return this->n;
}