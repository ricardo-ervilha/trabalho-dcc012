#include <iostream>
#include "BucketSort.h"
#include "MergeSort.h"

using namespace std;
#define BUCKET_SIZE 36

BucketSort::BucketSort(ProductReview *list, int n)
{
    this->list = list;
    this->registros = n;

    // cada posição guarda o ponteiro para uma lista
    buckets = new ListaEncad *[BUCKET_SIZE];

    listaOrdenada = new ListaEncad();

    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        buckets[i] = new ListaEncad();
    }
}

BucketSort::~BucketSort()
{
    delete list;
};

void BucketSort::ordena()
{
    for (int i = registros - 1; i--; i >= 0)
    {
        for (int j = 0; j <= i; j++)
        {
            // cout << " Comparando: " << list[j].getUserId() << " > " << list[j + 1].getUserId() << endl;
            if (list[j].getUserId() > list[j + 1].getUserId())
            {
                // cout << list[j].getUserId() << "   Maior do que " << list[j + 1].getUserId() << endl;
                ProductReview aux = list[j];
                list[j] = list[j + 1];
                list[j + 1] = aux;
            }
        }
    }
}

void BucketSort::sort()
{
    int pos;
    ProductReview aux;
    // P1: armazenar os registros nos baldes de acordo com o segundo caracter
    for (int i = 0; i < registros; i++)
    {
        // cout << "[" << list[i].getUserId()[1] << "]: " << list[i].getUserId() << endl;

        if (list[i].getUserId()[1] >= '0' && list[i].getUserId()[1] <= '9')
        {
            pos = (int)list[i].getUserId()[1] - '0';
        }
        else if (list[i].getUserId()[1] >= 'a' && list[i].getUserId()[1] <= 'z')
        {
            pos = (int)list[i].getUserId()[1] - 'a' + 10;
        }
        else if (list[i].getUserId()[1] >= 'A' && list[i].getUserId()[1] <= 'Z')
        {
            pos = (int)list[i].getUserId()[1] - 'A' + 10;
        }

        aux = list[i];
        // cout << "AUX: " << aux.getProductId();
        // cout << " LIST: " << list[i].getProductId() << endl;
        buckets[pos]->insereInicio(&list[i]); // TODO: Devo passar uma cópia ou a referencia do ProductReview???
    }

    // P2: ordenar cada balde
    // cout << "INSERTION SORT: " << endl;
    for (int b = 0; b < BUCKET_SIZE; b++)
    {
        // cout << "BALDE: " << b << " TAMANHO: " << buckets[b]->getSize() << endl;
        if (buckets[b]->getSize() < 2000)
        {
            this->insertionSort(b);
            this->concatBucket(b);
        }
        else
        {
            this->mergeSort(b);
        }
    }

    // this->insertionSort();
    // this->mergeSort();

    // P3: concatenar os baldes
    // cout << "CONCAT: " << endl;

    // pegar a posição do primeiro balde com lista não-
    /*int b;
    for (b = 0; buckets[b]->getSize() == 0; b++)
        ;

    listaOrdenada = buckets[b];
    for (int i = b + 1; i < BUCKET_SIZE; i++)
    {
        if (buckets[i]->getSize() != 0)
        {
            listaOrdenada->insereListaFinal(buckets[i]);
        }
    }*/

    // cout << "IMPRIMINDO LISTA COMPLETA: " << endl;
    //  listaOrdenada->printList();
}

void BucketSort::concatBucket(int b)
{
    if (buckets[b]->getSize() > 0)
    {
        listaOrdenada->insereListaFinal(buckets[b]);
    }
}
void BucketSort::insertionSort(int b)
{
    if (buckets[b]->getSize() > 0)
    {
        ListaEncad *listaBaldeN = buckets[b];
        for (int i = 0; i < listaBaldeN->getSize() - 1; i++)
        {
            int j = i + 1;
            int indexRemover = j + 1;
            ProductReview *pivo = listaBaldeN->get(j);
            while (j > 0 && pivo->getUserId() < listaBaldeN->get(j - 1)->getUserId())
                j--;
            listaBaldeN->insere(pivo, j);
            listaBaldeN->remove(indexRemover);
        }

        // cout << "BALDE: " << b << " TAMANHO: " << buckets[b]->getSize() << " CHARACTER: " << buckets[b]->get(0)->getUserId()[1] << endl;
        // buckets[b]->printList();
    }
}
/*void BucketSort::mergeSort()
{
    ListaEncad *concatMerge = new ListaEncad();
    for (int b = 0; b < BUCKET_SIZE; b++)
    {
        if (buckets[b]->getSize() > 0)
        {
            ListaEncad *lista = buckets[b];
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
                concatMerge->insereFinal(&aux[i]);
            }
        }
    }
    // cout << "LISTA CONCATENADA: " << endl;
    concatMerge->printList();
}*/
void BucketSort::mergeSort(int b)
{
    if (buckets[b]->getSize() > 0)
    {
        ListaEncad *lista = buckets[b];
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
}

void BucketSort::imprime()
{
    for (int b = 0; b < BUCKET_SIZE; b++)
    {
        if (buckets[b]->getSize() > 0)
        {
            // cout << " BALDE: " << b << endl;
            //cout << "BALDE: " << b << " TAMANHO: " << buckets[b]->getSize() << " CHARACTER: " << buckets[b]->get(0)->getUserId()[1] << endl;
            //buckets[b]->printList();
        }
    }
}