#ifndef LISTAENCADPRODUCTREVIEW_H
#define LISTAENCADPRODUCTREVIEW_H
#include "NoProductReview.h"

using namespace std;

class ListaEncadProductReview
{

private:
    NoProductReview *primeiro; // Ponteiro primeiro nó da lista.
    NoProductReview *ultimo;   // Ponteiro último nó da lista.
    int n;                     // Tamanho da lista.
    NoProductReview *ordenada;
public:
    ListaEncadProductReview();
    ~ListaEncadProductReview();
    bool busca(string idProduto);                // Busca um ProductReview utilizando seu productId
    ProductReview get(int k);                    // Retorna o ProductReview indice k
    void set(int k, ProductReview avaliacao);    // Seta no indice k um ProductReview
    void insere(ProductReview avaliacao, int k); // Insere no indice k um ProductReview
    void insereInicio(ProductReview avaliacao);
    void insereFinal(ProductReview avaliacao);
    void removeInicio();
    void removeFinal();
    void remove(int k); // Remove no indice k um ProductReview
    void printList();   // Imprime todos os elementos da lista
    int getSize();
    void insereListaFinal(ListaEncadProductReview *);
    NoProductReview *getPrimeiro() { return primeiro; }
    void setPrimeiro(NoProductReview * val) { this->primeiro = val; }
    void setUltimo(NoProductReview * val) { this->ultimo = val; }
    NoProductReview *getUltimo() { return ultimo; }
    void insertionSort();
    void sortedInsert(NoProductReview*);
};

#endif