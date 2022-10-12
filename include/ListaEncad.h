#ifndef LISTAENCAD_H
#define LISTAENCAD_H
#include "No.h"

using namespace std;

class ListaEncad{

private:
    No* primeiro;  //Ponteiro primeiro nó da lista.
    No* ultimo;    //Ponteiro último nó da lista.
    int n;         //Tamanho da lista.
public:
    ListaEncad();
    ~ListaEncad();
    bool busca(string idProduto);                       //Busca um ProductReview utilizando seu productId
    ProductReview* get(int k);                           //Retorna o ProductReview indice k
    void set(int k, ProductReview* avaliacao);           //Seta no indice k um ProductReview
    void insere(ProductReview* avaliacao, int k);        //Insere no indice k um ProductReview
    void insereInicio(ProductReview* avaliacao);
    void insereFinal(ProductReview* avaliacao);
    void removeInicio();
    void removeFinal();
    void remove(int k);                                 //Remove no indice k um ProductReview
    void printList();                                   //Imprime todos os elementos da lista
};

#endif