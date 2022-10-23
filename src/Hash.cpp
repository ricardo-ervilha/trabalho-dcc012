#include <iostream>
#include <cstdlib>
#include "Hash.h"

using namespace std;

Hash::Hash(int n){

    if(n == 10)
        tam = 7;
    else if(n == 100)
        tam = 71;
    else if(n == 1000)
        tam = 781;
    else if(n == 10000)
        tam = 10007; //primo perto de 10000
    else if(n == 50000)
        tam = 50033;
    else if(n == 100000)
        tam = 100103;
    else if(n == 500000)
        tam = 500069;
    else if(n == 1000000)
        tam = 1000121;
    else
        tam = n;

    vet = new List*[tam];
    inicializaTabela();
}

Hash::~Hash(){
    delete [] vet;
}

void Hash::inicializaTabela(){

    for(int i = 0; i < tam; i++)
    {
        List* lista = new List();
        vet[i] = lista;
    }
}

int Hash::funcaoHash(unsigned long long chave){
    return chave % tam;
}

void Hash::inserir(unsigned long long valor){
    int id = funcaoHash(valor);

    if(vet[id]->getN() == 0)
        vet[id]->insereInicio(valor);
    else
        vet[id]->insereFinal(valor);

}

bool Hash::busca(unsigned long long chave){
    int id = funcaoHash(chave);

    if(vet[id]->busca(chave))
        return true;
    else
        return false;
}

void Hash::imprime(){
    for(int i = 0; i < tam; i++){
        cout << "[" << i << "] ";
        vet[i]->imprimeLista();
    }
}
