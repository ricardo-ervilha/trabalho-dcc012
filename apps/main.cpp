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
            break;
        }
        case 2: {
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            BucketSort *bucket = new BucketSort(vet, n);
            bucket->sort();
            bucket->imprime();

            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            time_t end_time = chrono::system_clock::to_time_t(end);

            cout << "Bucket: Tempo para ordenar: " << elapsed_seconds.count() << "s\n";
            break;
        }
        
        default:
            cout << "Valor inválido." << endl;
            break;
    }
}

void hashFunction() {
    cout << "Nada pronto." << endl;
}

int main() {
    int opcao = 1;
    int methodId = 1;
    int n;
    string path = "/home/lucas/Estudo/UFJF/2022.3/DCC012/trabalho/trabalho-dcc012/";

    while (opcao != 3) {
        cout << "Digite um valor para executar a etapa desejada: " << endl;
        cout << "[1] Ordenacao." << endl;
        cout << "[2] Hash." << endl;
        cout << "[3] Encerrar aplicacao." << endl;

        cin >> opcao;
        switch (opcao) {
            case 1: {
                File *ratings = new File();
                ratings->createBinary(path);

                do {
                    ifstream inputDat;
                    inputDat.open("input.dat", ios::in);
                    string linha;
                    if(!inputDat){
                        cout << "Erro ao abrir input.dat"<<endl;
                        return 0;
                    }
                    getline(inputDat, linha);
                    cout <<"Registros a serem importados: "<<linha<<endl;
                    ProductReview *vet = ratings->import(stoi(linha));
                   
                    cout << "Digite qual metodo de ordenacao sera utilizado:" << endl;
                    cout << "[0] Merge Sort\n";
                    cout << "[1] Quick Sort\n";
                    cout << "[2] Bucket Sort\n";
                    cout << "[3] Retornar ao menu anterior\n";

                    cin >> methodId;
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