#include <iostream>
#include "QuickSort.h"
#include <chrono>

#define comparacoes 0
#define movimentacoes 1

using namespace std;
QuickSort::QuickSort(ProductReview *list, int n)
{
    this->list = list;
    this->registros = n;
}

QuickSort::~QuickSort()
{
    delete list;
};
void QuickSort::Troca(ProductReview i, ProductReview j)
{
    ProductReview aux;
    aux = i;
    i = j;
    j = aux;
}
int QuickSort::RandomPivo(int inicio, int fim)//Gera um pivô aleatório dentre os possíveis índices do vetor
{
    int posicao_pivo;
    posicao_pivo=inicio + rand() % (fim-inicio+1);
    return posicao_pivo;
}

int QuickSort:: Particiona(ProductReview *list, int inicio, int fim, int Comp_Mov[2])
{
    cout<<"Entrou no Particiona "<<fim<<endl;
    int posico_pivo = RandomPivo(inicio,fim);
    ProductReview pivo = list[posico_pivo];
    int i = inicio-1, j = fim+1;

    do
    {
        do
        {
            i++;

        } while (list[i].getUserId()<pivo.getUserId());
        do
        {
            j++;

        } while (list[j].getUserId()>pivo.getUserId());
        if(i >= j)
        {
            return j;
        }
        Troca(list[i],list[j]);     
    } while (true);
    
}

void QuickSort::QuickSortRec(ProductReview *list, int inicio, int fim, int Comp_Mov[2])
{
    cout<<"Entrou no QuickSortRec "<<fim<<endl;
    
    if(inicio < fim)
    {
        int posicao = Particiona(list, inicio, fim, Comp_Mov);
        QuickSortRec(list, inicio, posicao,Comp_Mov); //Processo recursivo para particionar até que chegar a partições ordenadas(partições unicas) 
        QuickSortRec(list,posicao+1, fim,Comp_Mov); 
    }
}
void QuickSort::sort()
{
    int Comp_Mov[2]={0,0};//Vetor onde a posição 0 conta o número de comparações e posição 1 conta o número de movimentações
    std::chrono::time_point<std::chrono::system_clock> start, end;

    cout<<"Entrou no Sort"<<endl;
    start = std::chrono::system_clock::now();

    QuickSortRec(list, 0, registros-1,Comp_Mov);

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Tempo de Ordenacao(Usando a Chrono): " << elapsed_seconds.count() << "s\n";
    cout<<"Numero de comparacoes: "<< Comp_Mov[comparacoes]<<endl;
    cout<<"Numero de movimentacoes: "<< Comp_Mov[movimentacoes]<<endl;  
    
}

void QuickSort::imprime()
{
    for (int i = 0; i < registros; i++)
    {
        cout << list[i].getUserId() << endl;
    }
}
