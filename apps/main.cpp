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

// Variáveis globais
string path;
int compMov[2] = {0, 0};            // vetor para acesso global do número de comparações e movimentações.
double medias[3] = {0.0, 0.0, 0.0}; // vetor para acesso global da média de comparações, movimentações e tempo dos ordenadores.

void sort(ProductReview *vet, int n, int methodId)
{
    switch (methodId)
    {
    case 0:
    {
        MergeSort *merge = new MergeSort(vet, n);
        merge->sort();
        compMov[comparacoes] = merge->getCompMov()[comparacoes];
        compMov[movimentacoes] = merge->getCompMov()[movimentacoes];
        break;
    }
    case 1:
    {
        QuickSort *quick = new QuickSort(vet, n);
        quick->sort();
        compMov[comparacoes] = quick->getCompMov()[comparacoes];
        compMov[movimentacoes] = quick->getCompMov()[movimentacoes];
        break;
    }
    case 2:
    {
        BucketSort *bucket = new BucketSort(vet, n);
        bucket->sort();
        compMov[comparacoes] = bucket->getCompMov()[comparacoes];
        compMov[movimentacoes] = bucket->getCompMov()[movimentacoes];
        break;
    }
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

void gerarSaida(int n)
{
    ofstream saida; // variável para gerar a saída com as estatísticas
    saida.open("saida.txt");
    File *ratings = new File();

    for (int j = 0; j < 3; j++)
    {
        for (int l = 0; l < 3; l++)
        {
            medias[l] = 0.0;
        }
        for (int i = 0; i < 3; i++)
        {
            ProductReview *vet = new ProductReview();
            if (j == 0)
            {
                saida << "MergeSort(" << i + 1 << ")" << endl;
            }
            if (j == 1)
            {
                saida << "QuickSort(" << i + 1 << ")" << endl;
            }
            if (j == 2)
            {
                saida << "BucketSort(" << i + 1 << ")" << endl;
            }
            vet = ratings->import(n);
            std::chrono::time_point<std::chrono::system_clock> start, end;

            start = std::chrono::system_clock::now();
            sort(vet, n, j);
            cout << endl;
            end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end - start;
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);

            saida << "----->   Comparacoes: " << compMov[comparacoes] << endl;
            medias[comparacoes] += compMov[comparacoes];

            saida << "----->   Movimentacoes: " << compMov[movimentacoes] << endl;
            medias[movimentacoes] += compMov[movimentacoes];

            saida << "----->    Tempo: " << elapsed_seconds.count() << endl;
            medias[tempo] += elapsed_seconds.count();
            saida << endl;

            compMov[comparacoes] = 0;
            compMov[movimentacoes] = 0;

            delete[] vet;
        }

        for (int k = 0; k < 3; k++)
        {
            medias[k] = (medias[k]) / 3;
        }

        if (j == 0)
        {
            saida << "************************************************************************" << endl;
            saida << "Medias MergeSort " << n << endl
                  << "Comparacoes: " << medias[comparacoes] << ", Movimentacoes: " << medias[movimentacoes] << ", Tempo: " << medias[tempo] << endl;
            saida << "************************************************************************" << endl
                  << endl;
        }
        if (j == 1)
        {
            saida << "************************************************************************" << endl;
            saida << "Medias QuickSort " << n << endl
                  << "Comparacoes: " << medias[comparacoes] << ", Movimentacoes: " << medias[movimentacoes] << ", Tempo: " << medias[tempo] << endl;
            saida << "************************************************************************" << endl
                  << endl;
        }
        if (j == 2)
        {
            saida << "************************************************************************" << endl;
            saida << "Medias BucketSort " << n << endl
                  << "Comparacoes: " << medias[comparacoes] << ", Movimentacoes: " << medias[movimentacoes] << ", Tempo: " << medias[tempo] << endl;
            saida << "************************************************************************" << endl
                  << endl;
        }
    }
    saida.close();
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
    while (opcao != 4)
    {
        methodId = 4;
        cout << "Digite um valor para executar a etapa desejada: " << endl;
        cout << "[1] Ordenacao." << endl;
        cout << "[2] Hash." << endl;
        cout << "[3] Gerar estatisticas de ordenação" << endl;
        cout << "[4] Encerrar aplicacao." << endl;
        cin >> opcao;
        ifstream inputDat;
        string linha;
        inputDat.open("data/input.dat", ios::in);
        switch (opcao)
        {
        case 1:
        {
            cin.ignore();

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

            ProductReview *vet;
            // chrono::time_point<chrono::system_clock> start, end;
            // start = chrono::system_clock::now();
            cout << "Registros a serem importados: " << linha << endl;
            vet = ratings->import(stoi(linha));
            // end = chrono::system_clock::now();
            // chrono::duration<double> elapsed_seconds = end - start;
            // time_t end_time = chrono::system_clock::to_time_t(end);

            // cout << "Tempo para importar: " << linha << ": " << elapsed_seconds.count() << "s\n";

            sort(vet, stoi(linha), methodId);

            break;
        }
        case 2:
            hashFunction();
            break;
        case 3:
            cin.ignore();
            if (!inputDat)
            {
                cout << "Erro ao abrir input.dat" << endl;
                return 0;
            }
            getline(inputDat, linha);
            gerarSaida(stoi(linha));
            inputDat.close();
            break;
        case 4:
            break;
        default:
            cout << "Valor invalido." << endl;
            break;
        }
    }

    return 0;
}