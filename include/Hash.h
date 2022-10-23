#ifndef HASH_H
#define HASH_H

#include "List.h"

class Hash{

private:
    int tam;
    List** vet;
    void inicializaTabela();
    

public:
    Hash(int n);
    ~Hash();
    void inserir(unsigned long long valor);
    bool busca(unsigned long long chave);
    void imprime();
    int funcaoHash(unsigned long long chave);
};



#endif