#include <iostream>
#include "BucketSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

using namespace std;
#define BUCKET_SIZE 46656

#define COMPARACOES 0
#define MOVIMENTACOES 1

BucketSort::BucketSort(ProductReview *vet, int n)
{
    this->vet = vet;
    this->n = n;
    this->compMov = new int[2];
    this->compMov[0] = 0;
    this->compMov[1] = 0;

    // cada posição guarda o ponteiro para uma lista
    buckets = new ListaEncadProductReview *[BUCKET_SIZE];

    listaOrdenada = new ListaEncadProductReview();

    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        buckets[i] = new ListaEncadProductReview();
    }
}
BucketSort::~BucketSort()
{
    delete vet;
};
// Bucket sort usando Merge/Quick Sort como algoritmo de ordenação intermediário
void BucketSort::sort()
{
    // P1: armazenar os registros nos baldes de acordo com o segundo caracter
    this->putInBuckets();

    int i = 0;

    for (int b = 0; b < BUCKET_SIZE; b++)
    {
        // P2: ordenar cada balde
        if (buckets[b]->getSize() > 1)
        {
            // ------------------------USANDO MERGE/QUICK SORT-------------

            // cria um vetor auxiliar com o tamanho do balde
            ProductReview *aux = new ProductReview[buckets[b]->getSize()];

            // passa os valores do balde na posição b para o vetor auxiliar
            int j = 0;
            NoProductReview *p;
            for (p = buckets[b]->getPrimeiro(); p != NULL; p = p->getProx())
            {
                aux[j++] = p->getInfo();
                this->compMov[MOVIMENTACOES] += 1;
            }

            // ordena o vetor auxiliar
            MergeSort *merge = new MergeSort(aux, buckets[b]->getSize());
            merge->sort();
            this->compMov[MOVIMENTACOES] += merge->getCompMov()[MOVIMENTACOES];
            this->compMov[COMPARACOES] += merge->getCompMov()[COMPARACOES];



            // P3: Concatenar os baldes
            while (j > 0)
            {
                vet[i++] = aux[--j];
                this->compMov[MOVIMENTACOES] += 1;
            }

            delete[] aux;
            // ------------------------USANDO MERGE/QUICK SORT-------------
        }
        else if (buckets[b]->getSize() == 1)
        { // se a lista encadeada no balde b tem tamanho 1, apenas passa o valor para o balde
            this->compMov[MOVIMENTACOES] += 1;
            vet[i++] = buckets[b]->getPrimeiro()->getInfo();
        }
    }
}
void BucketSort::putInBuckets()
{
    int pos;

    int c1, c2, c3;

    for (int i = 0; i < n; i++)
    {
        compMov[COMPARACOES] += 3;
        if (vet[i].getUserId()[1] >= '0' && vet[i].getUserId()[1] <= '9')
        {
            c1 = (vet[i].getUserId()[1] - '0');
        }
        else if (vet[i].getUserId()[1] >= 'a' && vet[i].getUserId()[1] <= 'z')
        {
            c1 = (vet[i].getUserId()[1] - 'a');
        }
        else if (vet[i].getUserId()[1] >= 'A' && vet[i].getUserId()[1] <= 'Z')
        {
            c1 = (vet[i].getUserId()[1] - 'A' + 10);
        }

        compMov[COMPARACOES] += 3;
        if (vet[i].getUserId()[2] >= '0' && vet[i].getUserId()[2] <= '9')
        {
            c2 = (vet[i].getUserId()[2] - '0');
        }
        else if (vet[i].getUserId()[2] >= 'a' && vet[i].getUserId()[2] <= 'z')
        {
            c2 = (vet[i].getUserId()[2] - 'a');
        }
        else if (vet[i].getUserId()[2] >= 'A' && vet[i].getUserId()[2] <= 'Z')
        {
            c2 = (vet[i].getUserId()[2] - 'A' + 10);
        }

        compMov[COMPARACOES] += 3;
        if (vet[i].getUserId()[3] >= '0' && vet[i].getUserId()[3] <= '9')
        {
            c3 = (vet[i].getUserId()[3] - '0');
        }
        else if (vet[i].getUserId()[3] >= 'a' && vet[i].getUserId()[3] <= 'z')
        {
            c3 = (vet[i].getUserId()[3] - 'a');
        }
        else if (vet[i].getUserId()[3] >= 'A' && vet[i].getUserId()[3] <= 'Z')
        {
            c3 = (vet[i].getUserId()[3] - 'A' + 10);
        }

        pos = c1 * 36 * 36 + c2 * 36 + c3;

        compMov[MOVIMENTACOES] += 1; // Inserção em lista encadeada é O(1), precisa incrementar aqui?
        buckets[pos]->insereInicio(vet[i]);
    }
}
void BucketSort::printBuckets()
{
    for (int b = 0; b < BUCKET_SIZE; b++)
    {
        if (buckets[b]->getSize() > 0)
        {
            // cout << " BALDE: " << b << endl;
            cout << "BALDE: " << b << " TAMANHO: " << buckets[b]->getSize() << " CHARACTER: " << buckets[b]->get(0).getUserId()[1] << endl;
            buckets[b]->printList();
        }
    }
}
void BucketSort::printVet()
{
    for (int i = 0; i < n; i++)
    {
        cout << "[" << i << "] \t" << vet[i].getUserId() << endl;
    }
}