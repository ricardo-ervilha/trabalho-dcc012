#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <time.h>
#include "ProductReview.h"
#include "ListaEncad.h"
#include "File.h"
#include <chrono>
#include "HashProduct.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "BucketSort.h"
#include <fstream>

using namespace std;
using namespace std::chrono;

void ordenacao(){
    int n;
    char opcao = '!';
    File *ratings = new File();
    std::chrono::time_point<std::chrono::system_clock> start, end;
                        

    cout << "Digite o tamanho de n que voce deseja: " << endl;
    cin >> n;

    ifstream ifile;
    ifile.open("ratings.bin");
   
    if(!ifile){
        cout << "Gerando binario..." << endl;
        ratings->createBinary(); //Alterar para adicionar o caminho da pasta.
    }

    start = std::chrono::system_clock::now();
    ProductReview *vet = ratings->import(n);
    end = std::chrono::system_clock::now();

    
    MergeSort *merge = new MergeSort(vet, n);
    QuickSort *quick = new QuickSort(vet, n);
    BucketSort *bucket = new BucketSort(vet, n);

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Tempo para importar dados: " << elapsed_seconds.count() << "s\n";

    while(opcao != '3'){
        cout << "Digite qual metodo de ordenacao sera utilizado:" << endl;
        cout << "[0] Merge Sort\n";
        cout << "[1] Quick Sort\n";
        cout << "[2] Bucket Sort\n";
        cout << "[3] Retornar ao menu anterior\n";
        cin >> opcao;
        switch(opcao){
            case '0':   merge->sort();
                        opcao = '3';
                        break;
            case '1':   quick->sort();
                        opcao = '3';
                        break;
            case '2':   bucket->sort();
                        opcao = '3';
                        break;
            case '3':   break;

            default:  cout << "Valor inválido." << endl;   break;
        }
    }

}

void hashFunction(){
    cout << "Nada pronto." << endl;
}

int main(){
    char opcao = '!';
    
    while(opcao != '3'){
        cout << "Digite um valor para executar a etapa desejada: " << endl;
        cout << "[1] Ordenacao." << endl; 
        cout << "[2] Hash." << endl;
        cout << "[3] Encerrar aplicacao." << endl;
        
                                    
        cin >> opcao;
        switch(opcao){
            case '1':   ordenacao();
                        break;
            case '2':   hashFunction();
                        break;
            case '3':   break;
            
            default:  cout << "Valor inválido." << endl;   break;         
        }
    }
    
    return 0;
}