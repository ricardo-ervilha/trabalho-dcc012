#include <iostream>
#include "BucketSort.h"

using namespace std;

BucketSort::BucketSort(ProductReview *list, int n)
{
    this->list = list;
    this->registros = n;
}

BucketSort::~BucketSort()
{
    delete list;
};

void BucketSort::sort()
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

void BucketSort::imprime()
{
    for (int i = 0; i < registros; i++)
    {
        cout << list[i].getUserId() << endl;
    }
}