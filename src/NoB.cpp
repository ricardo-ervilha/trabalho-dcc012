#include "NoB.h"

NoB::NoB()
{
    this->n = 0;
    //DISK-WRITE(esse no)
}

NoB::~NoB()
{
}

/*
    Faz cisão do nó e insere Info
*/
NoB *NoB::cisao(Info novaInfo)
{
    int qtdNo = n / 2.0; // quantidade de registros no nó atual (esquerda)
    NoB *novo = new NoB();
    novo->ehFolha = this->ehFolha;
    int count = 0;

    // procurar posição para inserir
    int pos;
    for (pos = 0; chaves[pos].id < novaInfo.id && pos < n; pos++)
        ;

    Info separador;

    if (pos <= qtdNo)
    {
        // lado esq maior do que lado direito
        // pivo sera ultimo da primeira parte

        for (int i = qtdNo; i < n; i++)
        {
            novo->chaves[count++] = chaves[i];
        }
        novo->n = count;
        n = n - count; // quantidade do no a esquerda antes de inserir

        // deslocar pra direita, começando do final
        for (int i = qtdNo; i > pos; i--)
        {
            chaves[i] = chaves[i - 1];
        }

        // salvar o novo valor na posição pos a esquerda
        chaves[pos] = novaInfo;
        n = n + 1;

        separador = chaves[n - 1];
        n = n - 1; // o separador vai subir
    }
    else
    {
        // lado direito maior do que lado esquerdo
        // pivo sera primeiro da segunda parte
        for (int i = qtdNo + 1; i < n; i++)
        {
            novo->chaves[count++] = chaves[i];
        }
        novo->n = count;
        n = n - count; // conferir

        separador = chaves[qtdNo];
        n = n - 1; // o separador vai subir

        int k = pos - qtdNo - 1; // local que vai ser inserida a info no novo

        // deslocar pra direita, começando do final
        for (int i = count; i > k; i--)
        {
            novo->chaves[i] = novo->chaves[i - 1];
        }

        novo->chaves[k] = novaInfo;
        novo->n = novo->n + 1;
    }
    return novo;
}

// NoB NoB::inserir(Info info)
// {
//     if (!cheio())
//     {
//         // procurar posição para inserir
//         int pos;
//         for (pos = 0; chaves[pos].id < info.id && pos < n; pos++)
//             ;

//         // deslocar pra direita, começando do final
//         for (int i = n; i > pos; i--)
//         {
//             chaves[i] = chaves[i - 1];
//         }

//         // salvar o novo valor na posição pos
//         chaves[pos] = info;
//         this->n = this->n + 1;
//     }
// }


