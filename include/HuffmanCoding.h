#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include <iostream>
#include "NoHuff.h"

using namespace std;

typedef struct{
    NoHuff *inicio;
    int tam;

}HuffList;

class HuffmanCoding{
private:
    string path;
    int *table_freq;
    HuffList *lista;
    
    void inicializa_com_zeros();
    void inicializa_Lista();
    NoHuff* remove_node_inicial();
    void insere_ordenado(NoHuff *node);

public:
    HuffmanCoding();
    ~HuffmanCoding();
    
    NoHuff* create_arvore_huffman();
    void imprime_lista_prioridade();
    void preenche_lista_prioridade();
    void contabilizaFrequencia(int n);
};

#endif