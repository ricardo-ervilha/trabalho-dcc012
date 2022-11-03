#include <iostream>
#include "MergeSort.h"
#include <chrono>

#define comparacoes 0
#define movimentacoes 1

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
void MergeSort::Merge(ProductReview *list, ProductReview *Aux, int inicio, int meio, int fim, int Comp_Mov[2])
{
    int i = inicio, j = meio + 1, k = 0;
    //cout<<"Entrou no Merge "<<meio<<endl;
    while(i <= meio && j <= fim)
    {
        Comp_Mov[comparacoes]++;
        if(list[i].getUserId() <= list[j].getUserId())
        {
            Comp_Mov[comparacoes]++;//Acrescenta ao número de comparações em 2 
            Aux[k] = list[i];
            Comp_Mov[movimentacoes]++;//Acrescente ao número de movimentações
            i++;
        }
        else
        {
            Comp_Mov[comparacoes]++;
            Aux[k] = list[j];
            Comp_Mov[movimentacoes]++;
            j++;
        }
        k++;
    }
    while(i <= meio)
    {
        Comp_Mov[comparacoes]++;
        Aux[k] = list[i];
        Comp_Mov[movimentacoes]++;
        i++;
        k++;
    }
    while(j <= fim)
    {
        Comp_Mov[comparacoes]++;
        Aux[k] = list[j];
        Comp_Mov[movimentacoes]++;
        j++;
        k++;
    }

    for(k = 0; k < fim-inicio+1; k++)
    {
        Comp_Mov[comparacoes]++;
        list[inicio+k] = Aux[k];
        Comp_Mov[movimentacoes]++;
    }
}
void MergeSort::MergeSortRec(ProductReview *list, ProductReview *Aux, int inicio, int fim, int Comp_Mov[2])
{
    //cout<<"Entrou no MergeSortRec "<<fim<<endl;
    
    if(inicio < fim)
    {
        Comp_Mov[comparacoes]++;//Acrescenta no número de comparações
        int meio = (inicio+fim)/2;

        MergeSortRec(list, Aux, inicio, meio,Comp_Mov); //Processo recursivo para particionar até que chegar a partições ordenadas(partições unicas) 
        MergeSortRec(list, Aux, meio+1, fim,Comp_Mov);

        Merge(list, Aux, inicio, meio, fim,Comp_Mov);//Ordena as duas partições entre si
    }
}
void MergeSort::sort()
{
    ProductReview *Aux = new ProductReview[registros];
    int Comp_Mov[2]={0,0};//Vetor onde a posição 0 conta o número de comparações e posição 1 conta o número de movimentações
    std::chrono::time_point<std::chrono::system_clock> start, end;
    //cout<<"Entrou no Sort"<<endl;
    start = std::chrono::system_clock::now();

    MergeSortRec(list, Aux, 0, registros-1,Comp_Mov);
    delete  [] Aux;

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Tempo de Ordenacao(Usando a Chrono): " << elapsed_seconds.count() << "s\n";
    cout<<"Numero de comparacoes: "<< Comp_Mov[comparacoes]<<endl;
    cout<<"Numero de movimentacoes: "<< Comp_Mov[movimentacoes]<<endl;  
    
}

void MergeSort::imprime()
{
    for (int i = 0; i < registros; i++)
    {
        cout << list[i].getUserId() << endl;
    }
}
