#include <iostream>
#include "QuickSort.h"
#include <chrono>
#include <fstream>
#define comparacoes 0
#define movimentacoes 1

using namespace std;
QuickSort::QuickSort(ProductReview *list, int n)
{
    this->Comp_Mov = new int [2];
    this->Comp_Mov[comparacoes] = 0 ;
    this->Comp_Mov[movimentacoes] = 0;
    this->list = list;
    this->registros = n;
}

QuickSort::~QuickSort()
{
    delete list;
};
void QuickSort::Troca(ProductReview *list, int i, int j, int Comp_Mov[2])
{
    //cout<<"Entrou no troca i="<<i<<" j="<<j<<endl;
    ProductReview *aux= new ProductReview [1];
    aux[0] = list[i]; 
    list[i] = list[j];//troca o regitsro indice i
    list[j]= aux[0];//troca o registro indice j
    Comp_Mov[movimentacoes]++; //Acrescenta o número de movimentação
    delete [] aux;
}
int QuickSort::RandomPivo(int inicio, int fim)//Gera um pivô aleatório dentre os possíveis índices do vetor
{
    int posicao_pivo;
    posicao_pivo=inicio + (rand() % (fim-inicio+1));
    //cout<<"Pivo "<<posicao_pivo<<" inicio "<<inicio<<" fim "<<fim<<endl;
    return posicao_pivo;
}

int QuickSort:: Particiona(ProductReview *list, int inicio, int fim, int Comp_Mov[2])
{
    //cout<<"Entrou no Particiona "<<fim<<endl;
    int posico_pivo = RandomPivo(inicio,fim);
    ProductReview pivo = list[posico_pivo];
    int i = inicio, j = fim;
    //cout<<"i = "<<i<<" j="<<j<<endl;

    while(true){
        while(list[i].getUserId()<pivo.getUserId()){
            //cout << "valor de i: " << i << endl;
            Comp_Mov[comparacoes] += 1;
            i++;
        }
        while(list[j].getUserId()>pivo.getUserId()){
            //cout << "valor de j: " << j << endl;
            Comp_Mov[comparacoes] += 1;
            j--;
        }
        if(i >= j)
        {    
             //cout << "valor de j retornado: " << j << endl;
             return j;
        }
        //cout << "Trocou i = " << i << " por j = " << j << endl;
        Troca(list,i,j, Comp_Mov);
        i++;
        j--;
    }
}

void QuickSort::QuickSortRec(ProductReview *list, int inicio, int fim, int Comp_Mov[2])
{
    //cout<<"Entrou no QuickSortRec "<<fim<<endl;
    
    if(inicio < fim)
    {
        int posicao = Particiona(list, inicio, fim, Comp_Mov);
        QuickSortRec(list, inicio, posicao,Comp_Mov); //Processo recursivo para particionar até que chegar a partições ordenadas(partições unicas) 
        QuickSortRec(list,posicao+1, fim,Comp_Mov); 
    }
}
void QuickSort::sort()
{
    
    srand(time(NULL));//Gerar sementes diferentes a cada execução
    //cout<<"Quick"<<endl;
    QuickSortRec(list, 0, registros-1,Comp_Mov);
    // cout<<"Numero de comparacoes: "<< Comp_Mov[comparacoes]<<endl;
    // cout<<"Numero de movimentacoes: "<< Comp_Mov[movimentacoes]<<endl;
}

void QuickSort::imprime()
{
    for (int i = 0; i < registros; i++)
    {
        //cout << list[i].getUserId() << endl;
    }
}
