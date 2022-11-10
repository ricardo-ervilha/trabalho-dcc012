/*
TODO:
    - Na hora de inserir na lista encadeada de cada balde, devo passar uma referência ou uma cópia do registro no vetor?
    - Como fazer para passar os nós da lista encadeada para o vet???
    - Dividir usando 3 char para ver se melhora  desempenho
    - Ignorar caracteres que representam o balde ao fazer a compração das strings
*/
#include <iostream>
#include "BucketSort.h"
#include "MergeSort.h"

using namespace std;
#define BUCKET_SIZE 46656

BucketSort::BucketSort(ProductReview *vet, int n)
{
    this->vet = vet;
    this->n = n;

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

void BucketSort::sort()
{
    // P1: armazenar os registros nos baldes de acordo com o segundo caracter
    this->putInBuckets();

    // P2: ordenar cada balde
    for (int b = 0; b < BUCKET_SIZE; b++)
    {
        if (buckets[b]->getSize() > 1)
        {
            buckets[b]->insertionSort();
            // this->insertionSort(b);
        }
        // this->mergeSort(b);
    }

    int i = 0;
    for (int b = 0; b < BUCKET_SIZE; b++)
    {
        // P3: Concatenar os baldes
        // this->concatBucket(b);
        NoProductReview *p;
        for (p = buckets[b]->getPrimeiro(); p != NULL; p = p->getProx())
        {
            vet[i++] = p->getInfo();
        }
    }
}
/*void BucketSort::listToArray()
{
    NoProductReview *p;
    // cout << "_Lista Encadeada_" << endl;
    int i = 0;
    for (p = listaOrdenada->getPrimeiro(); p != NULL; p = p->getProx(), i++)
    {
        cout << "- " << i << " - " << p->getInfo().getUserId() << endl;
        vet[i] = p->getInfo();
    }
}*/
/*void BucketSort::putInBuckets()
{
    int pos;
    ProductReview aux;
    for (int i = 0; i < n; i++)
    {
        // cout << "[" << vet[i].getUserId()[1] << "]: " << vet[i].getUserId() << endl;

        if (vet[i].getUserId()[1] >= '0' && vet[i].getUserId()[1] <= '9')
        {
            pos = (int)vet[i].getUserId()[1] - '0';
        }
        else if (vet[i].getUserId()[1] >= 'a' && vet[i].getUserId()[1] <= 'z')
        {
            pos = (int)vet[i].getUserId()[1] - 'a' + 10;
        }
        else if (vet[i].getUserId()[1] >= 'A' && vet[i].getUserId()[1] <= 'Z')
        {
            pos = (int)vet[i].getUserId()[1] - 'A' + 10;
        }
        buckets[pos]->insereInicio(vet[i]); // TODO: Devo passar uma cópia ou a referencia do ProductReview???
    }
}*/
/*void BucketSort::putInBuckets()
{
    int pos;

    int c1, c2;

    for (int i = 0; i < n; i++)
    {
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

        pos = c1 * 36 + c2;
        // cout << "[" << vet[i].getUserId()[1] << vet[i].getUserId()[2] << "]: " << vet[i].getUserId() << endl;
        // cout << "Conta: " << c1 << " * 36 + " << c2<< " = "<<pos<<endl;

        buckets[pos]->insereInicio(vet[i]);
    }
}*/
void BucketSort::putInBuckets()
{
    int pos;

    int c1, c2, c3;

    for (int i = 0; i < n; i++)
    {
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

        buckets[pos]->insereInicio(vet[i]);
    }
}
/*void BucketSort::concatBucket(int b)
{
    if (buckets[b]->getSize() > 0)
    {
        cout << "CONCATENANDO BALDE " << b << ", tamanho = " << buckets[b]->getSize() << " na lista" << endl;
        listaOrdenada->insereListaFinal(buckets[b]);
    }
}*/
void BucketSort::insertionSort(int b)
{
    if (buckets[b]->getSize() > 1)
    {
        ListaEncadProductReview *listaBaldeN = buckets[b];

        for (int i = 0; i < listaBaldeN->getSize() - 1; i++)
        {
            int j = i + 1;
            int indexRemover = j + 1;
            ProductReview pivo = listaBaldeN->get(j);
            while (j > 0 && pivo.getUserId() < listaBaldeN->get(j - 1).getUserId())
                j--;

            // significa que entrou no while pelo menos uma vez
            if (j < (i + 1))
            {
                listaBaldeN->insere(pivo, j);
                listaBaldeN->remove(indexRemover);
            }
        }

        // cout << "BALDE: " << b << " ORDENADO - TAMANHO: " << buckets[b]->getSize() << " CHARACTER: " << buckets[b]->get(0).getUserId()[1] <<buckets[b]->get(0).getUserId()[2]<< endl;
        // buckets[b]->printList();
    }
}
/*void BucketSort::mergeSort(int b)
{
    if (buckets[b]->getSize() > 0)
    {
        ListaEncadProductReview *lista = buckets[b];
        ProductReview *aux = new ProductReview[lista->getSize()];

        // passar todos elementos do balde b (lista encadeada) para o vetor aux
        for (int i = 0; i < lista->getSize(); i++)
        {
            aux[i] = *lista->get(i);
        }

        // ordenar
        MergeSort *merge = new MergeSort(aux, lista->getSize());
        merge->sort();

        for (int i = 0; i < lista->getSize(); i++)
        {
            listaOrdenada->insereFinal(&aux[i]);
        }
    }
}*/
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