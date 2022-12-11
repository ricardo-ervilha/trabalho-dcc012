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
    int altura;
    char **dicionario;
    
    void aux_preenche_Dicionario(NoHuff *p, string caminho, int coluna);
    int aux_calcula_altura_arvore(NoHuff *p);
    void inicializa_com_zeros();
    void inicializa_Lista();
    NoHuff* remove_node_inicial();
    void insere_ordenado(NoHuff *node);
    void gera_Dicionario();

public:
    HuffmanCoding();
    ~HuffmanCoding();
    
    void impressao_dicionario();
    void preenche_Dicionario();
    void contabiliza_Frequencia_string(string s);
    NoHuff* create_arvore_huffman();
    void imprime_lista_prioridade();
    void preenche_lista_prioridade();
    void contabilizaFrequencia(int n);
    void calcula_altura_arvore();
};

#endif