#include <iostream>
#include "MergeSort.h"
#include <chrono>

using namespace std::chrono;
using namespace std;

MergeSort::MergeSort(ProductReview *list, int n)
{
    this->list = list;
    this->registros = n;
}

MergeSort::~MergeSort()
{
    delete list;
};
void MergeSort::Merge(ProductReview *list, ProductReview *Aux, int inicio, int meio, int fim)
{
    int i = inicio, j = meio + 1, k = 0;
    //cout<<"Entrou no Merge "<<meio<<endl;
    while(i <= meio && j <= fim)
    {
        if(list[i].getUserId() <= list[j].getUserId())
        {
            Aux[k] = list[i];
            i++;
        }
        else
        {
            Aux[k] = list[j];
            j++;
        }
        k++;
    }
    while(i <= meio)
    {
        Aux[k] = list[i];
        i++;
        k++;
    }
    while(j <= fim)
    {
        Aux[k] = list[j];
        j++;
        k++;
    }

    for(k = 0; k < fim-inicio+1; k++)
    {
        list[inicio+k] = Aux[k];
    }
}
void MergeSort::MergeSortRec(ProductReview *list, ProductReview *Aux, int inicio, int fim)
{
    //cout<<"Entrou no MergeSortRec "<<fim<<endl;
    if(inicio < fim)
    {
        int meio = (inicio+fim)/2;
        MergeSortRec(list, Aux, inicio, meio); //Processo recursivo para particionar até que chegar a partições ordenadas(partições unicas) 
        MergeSortRec(list, Aux, meio+1, fim);
        Merge(list, Aux, inicio, meio, fim);//Ordena as duas partições entre si
    }
}
void MergeSort::sort()
{
    ProductReview *Aux = new ProductReview[registros];
    // Get starting timepoint
    auto start = high_resolution_clock::now();
    //cout<<"Entrou no Sort"<<endl;
    MergeSortRec(list, Aux, 0, registros-1);
    delete  [] Aux;
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo de ordenaçaõ: "<< duration.count()/1000000 << " microseconds" << endl;
}

void MergeSort::imprime()
{
    for (int i = 0; i < registros; i++)
    {
        cout << list[i].getUserId() << endl;
    }
}
