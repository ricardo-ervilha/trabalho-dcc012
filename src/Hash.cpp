#include <iostream>
#include <cstdlib>
#include "Hash.h"

using namespace std;

Hash::Hash(int n){
    if(n == 10)
        tam = 5;
    else if(n == 100)
        tam = 59;
    else if(n == 1000)
        tam = 577;
    else if(n == 10000)
        tam = 7109; 
    else if(n == 50000)
        tam = 31051;
    else if(n == 100000)
        tam = 57593;
    else if(n == 500000)
        tam = 310049;
    else if(n == 1000000)
        tam = 535099;
    else
        tam = (int) (0.637 * n);
        
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
    //cout<<"tamanho tam "<< tam <<endl;
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
