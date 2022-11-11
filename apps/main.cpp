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

//Variável global
string path;

void sort(ProductReview *vet, int n, int methodId) {
    switch (methodId) {
        case 0: {
            MergeSort *merge = new MergeSort(vet, n);
            merge->sort();
            break;
        }
        case 1: {
            QuickSort *quick = new QuickSort(vet, n);
            quick->sort();
            quick->imprime();
            break;
        }
        case 2: {
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            BucketSort *bucket = new BucketSort(vet, n);
            // cout <<endl<<"VET ANTES DE ORDENAR:..."<<endl;
            // for(int i =0;i<n;i++){
            //     cout << "[" << i << "] \t" << vet[i].getUserId() << endl;
            // }
            bucket->sort();
            // cout <<endl<<"VET DEPOIS DE ORDENAR:..."<<endl;
            // for(int i =0;i<n;i++){
            //     cout << "[" << i << "] \t" << vet[i].getUserId() << endl;
            // }

            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            time_t end_time = chrono::system_clock::to_time_t(end);

            cout << "Bucket: Tempo para ordenar: " << elapsed_seconds.count() << "s\n";
            break;
        }
        
        default:
            cout << "Valor invalido." << endl;
            break;
    }
}

void hashFunction() {
    HashProduct *hashTeste = new HashProduct(path);

    hashTeste->createTable(10000);
    hashTeste->printTable();
}

int main() {
    int opcao = 1;
    int methodId = 1;

    cout << "Digite a pasta onde o arquivo binario deve estar: " << endl;
    //getline(cin, path); 
    path = "/home/ricardo/dcc-012/trabalho-dcc012/";
    File *ratings = new File(path);
    ratings->createBinary(path);

    while (opcao != 3) {
        cout << "Digite um valor para executar a etapa desejada: " << endl;
        cout << "[1] Ordenacao." << endl;
        cout << "[2] Hash." << endl;
        cout << "[3] Encerrar aplicacao." << endl;
        cin >> opcao;
        switch (opcao) {
            case 1: {
                cin.ignore();
                
                do {
                    ifstream inputDat;
                    inputDat.open("data/input.dat", ios::in);
                    string linha;
                    
                    cout << "Digite qual metodo de ordenacao sera utilizado:" << endl;
                    cout << "[0] Merge Sort\n";
                    cout << "[1] Quick Sort\n";
                    cout << "[2] Bucket Sort\n";
                    cout << "[3] Retornar ao menu anterior\n";

                    cin >> methodId;

                    if(!inputDat){
                        cout << "Erro ao abrir input.dat"<<endl;
                        return 0;
                    }
                    getline(inputDat, linha);

                    chrono::time_point<chrono::system_clock> start, end;
                    start = chrono::system_clock::now();

                    cout <<"Registros a serem importados: "<<linha<<endl;
                    ProductReview *vet = ratings->import(stoi(linha));

                    end = chrono::system_clock::now();
                    chrono::duration<double> elapsed_seconds = end - start;
                    time_t end_time = chrono::system_clock::to_time_t(end);

                    cout << "Tempo para importar: "<<linha<<": " << elapsed_seconds.count() << "s\n";

                    sort(vet, stoi(linha), methodId);

                } while (methodId != 3);
                break;
            }
            case 2:
                hashFunction();
                break;
            case 3:
                break;

            default:
                cout << "Valor invalido." << endl;
                break;
        }
    }

    return 0;
}