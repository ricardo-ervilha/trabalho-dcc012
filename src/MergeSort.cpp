#include <iostream>
#include "MergeSort.h"
#include <chrono>
#include <fstream>
#define comparacoes 0
#define movimentacoes 1
#define tempo 2

using namespace std;

MergeSort::MergeSort(ProductReview *list, int n)
{
    this->Comp_Mov = new int [2];
    this->Comp_Mov[comparacoes]= 0 ;
    this->Comp_Mov[movimentacoes] = 0;
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
        Comp_Mov[comparacoes]++;//Acrescenta ao número de comparações
        Comp_Mov[movimentacoes]++;//Acrescente ao número de movimentações
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
        Comp_Mov[comparacoes]++;
        Comp_Mov[movimentacoes]++;
        Aux[k] = list[i];
        i++;
        k++;
    }
    while(j <= fim)
    {
        Comp_Mov[comparacoes]++;
        Comp_Mov[movimentacoes]++;
        Aux[k] = list[j];
        j++;
        k++;
    }

    for(k = 0; k < fim-inicio+1; k++)
    {
        Comp_Mov[movimentacoes]++;
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
    //cout<<"Entrou no Sort"<<endl;
    ProductReview *Aux = new ProductReview[registros];
    

    MergeSortRec(list, Aux, 0, registros-1);
    delete  [] Aux;
    
}

void MergeSort::imprime()
{
    for (int i = 0; i < registros; i++)
    {
        cout << list[i].getUserId() << endl;
    }
}
