#include "NoB.h"

NoB::NoB()
{
    this->n = 0;
}


NoB::~NoB()
{
}

NoB *NoB::cisao(Info novaInfo)
    {
        int qtdNo = ceil(n / 2.0); // quantidade de registros no nó atual
        NoB *novo = new NoB();
        novo->ehFolha = this->ehFolha;
        int count = 0; 

        for (int i = qtdNo; i < n; i++)
        {
            novo->chaves[count++] = chaves[i];
        }

        novo->n = count;
        n = n - count - 1;//-1 pois o ultimo elemento do no antigo vai ser promovido

        inserir(novaInfo);//tem que verificar se vai ser inserido no no atual ou no novo no

        return novo;
    }