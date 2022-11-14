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

#define comparacoes 0
#define movimentacoes 1
#define tempo 2

using namespace std;
using namespace std::chrono;

// Variável global
string path;

void sort(ProductReview *vet, int n, int methodId)
{
    double medias[3]; // vetor para guardar as medias a cada chamada dos ordenadores; 0 = comparacoes, 1 =  movimentacoes, 2 = tempo.
    ofstream saida;   // variável para gerar a saída com as estatísticas
    saida.open("saida.txt", ios::app);
    switch (methodId)
    {
        for (int i = 0; i < 3; i++)
        {
            medias[i] = 0.0;
        }
        case 0:
        {
            for (int m = 1; m < 4; m++)
            {
                saida << "MergeSort para " << n << " valores (" << m << "):" << endl;
                MergeSort *merge = new MergeSort(vet, n);
                std::chrono::time_point<std::chrono::system_clock> start, end;
                start = std::chrono::system_clock::now();
                merge->sort();
                end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::time_t end_time = std::chrono::system_clock::to_time_t(end); 
                std::cout << "Tempo de Ordenacao(Usando a Chrono): " << elapsed_seconds.count() << "s\n";
                //cout<<"Numero de comparacoes: "<< Comp_Mov[0]<<endl;
                //cout<<"Numero de movimentacoes: "<< Comp_Mov[1]<<endl;

                saida<< "----->   Comparacoes: "<<merge->getCompMov()[comparacoes]<<endl;
                medias[comparacoes]+=merge->getCompMov()[comparacoes];
                saida<< "----->   Movimentacoes: "<<merge->getCompMov()[movimentacoes]<<endl;
                medias[movimentacoes]+=merge->getCompMov()[movimentacoes];
                saida<< "----->    Tempo: "<<elapsed_seconds.count()<<endl<<endl;
                medias[tempo]+=elapsed_seconds.count();
                medias[0]+=merge->getCompMov()[0];

                //merge->imprime();
            }
            for (int i = 0; i < 3; i++)
            {
                medias[i] = medias[i] / 3;
            }
            saida << "************************************************************************\n";
            saida << "Medias MergeSort " << n << ":\nComparacoes: " << medias[0] << ", Movimentacoes: " << medias[1] << ", Tempo: " << medias[2] << endl;
            saida << "************************************************************************\n\n";
            break;
        }
        case 1:
        {
            for (int m = 1; m < 4; m++)
            {
                saida << "QuickSort para " << n << " valores (" << m << "):" << endl;
                QuickSort *quick = new QuickSort(vet, n);
                quick->sort();
            }
            break;
        }
        case 2:
        {
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
            saida.close();
        default:
            cout << "Valor invalido." << endl;
            break;
    }
}

void hashFunction()
{
    HashProduct *hashTeste = new HashProduct(path);

    hashTeste->createTable(100);
    hashTeste->printTable();

    int p;
    cout << "Digite o valor de p: " << endl;
    cin >> p;

    hashTeste->hashEtapa3(p);
}

int main()
{
    int opcao = 1;
    int methodId;
    string path;

    cout << "Digite a pasta onde o arquivo binario deve estar: " << endl;
    getline(cin, path);
    // path = "/home/ricardo/dcc-012/trabalho-dcc012/";
    // path = "/EDII/trabalho-dcc012/";
    File *ratings = new File();
    ratings->createBinary(path);
    while (opcao != 3)
    {
        methodId = 4;
        cout << "Digite um valor para executar a etapa desejada: " << endl;
        cout << "[1] Ordenacao." << endl;
        cout << "[2] Hash." << endl;
        cout << "[3] Encerrar aplicacao." << endl;
        cin >> opcao;
        switch (opcao)
        {
            case 1:
            {
                cin.ignore();

                ifstream inputDat;
                inputDat.open("data/input.dat", ios::in);
                string linha;

                while (methodId != 0 && methodId != 1 && methodId != 2 && methodId != 3)
                {

                    cout << "Digite qual metodo de ordenacao sera utilizado:" << endl;
                    cout << "[0] Merge Sort\n";
                    cout << "[1] Quick Sort\n";
                    cout << "[2] Bucket Sort\n";
                    cout << "[3] Retornar ao menu anterior\n";

                    cin >> methodId;
                    if (methodId != 0 && methodId != 1 && methodId != 2 && methodId != 3)
                    {
                        cout << "Valor invalido" << endl;
                    }
                }

                if (!inputDat)
                {
                    cout << "Erro ao abrir input.dat" << endl;
                    return 0;
                }

                getline(inputDat, linha);

                chrono::time_point<chrono::system_clock> start, end;
                start = chrono::system_clock::now();

                cout << "Registros a serem importados: " << linha << endl;
                ProductReview *vet;
                vet = ratings->import(stoi(linha));
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                time_t end_time = chrono::system_clock::to_time_t(end);

                cout << "Tempo para importar: " << linha << ": " << elapsed_seconds.count() << "s\n";

                sort(vet, stoi(linha), methodId);

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