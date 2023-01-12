#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <time.h>
#include "ProductReview.h"
#include "File.h"
#include <chrono>
#include "HashProduct.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "BucketSort.h"
#include <fstream>
#include "HuffmanCoding.h"

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

    int n;
    cout << "Digite o tamanho de n: " <<endl;
    cin >> n; 
    hashTeste->createTable(n);
    hashTeste->printTable();

    int p;
    cout << "Digite o valor de p: " << endl;
    cin >> p;

    hashTeste->hashEtapa3(p);
}

void gerarSaida()
{
    ifstream inputDat;
    string linha;
    inputDat.open("data/input.dat", ios::in);

    cin.ignore();
    if (!inputDat)
    {
        cout << "Erro ao abrir input.dat" << endl;
        return;
    }

    ofstream saida; // variável para gerar a saída com as estatísticas
    saida.open("saida.txt");
    File *ratings = new File(path);
    int n;
    // Gera o arquivo de saída para número de registros do inputDat
    while (getline(inputDat, linha))
    {
        n = stoi(linha);
        cout << "Gerando saída para " << n << " registros" << endl;

        // Para cada método de ordenação 0 - Merge, 1 - Quick e 2 - Bucket
        for (int j = 0; j < 3; j++)
        {
            for (int l = 0; l < 3; l++)
            {
                medias[l] = 0.0;
            }

            // Roda 3 vezes para cada método de ordenação
            for (int i = 0; i < 3; i++)
            {
                if (j == 0)
                {
                    saida << "MergeSort(" << i + 1 << ")" << endl;
                    cout << "MergeSort(" << i + 1 << ")" << endl;
                }
                if (j == 1)
                {
                    saida << "QuickSort(" << i + 1 << ")" << endl;
                    cout << "QuickSort(" << i + 1 << ")" << endl;
                }
                if (j == 2)
                {
                    saida << "BucketSort(" << i + 1 << ")" << endl;
                    cout << "BucketSort(" << i + 1 << ")" << endl;
                }
                ProductReview *vet = ratings->import(n);
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
    }
    saida.close();
    inputDat.close();
}

void comprime(int metodo){
    
    string txt = "";
    string pathTxt = path + "reviewsOrig.txt";
    string pathBin = path + "reviewsComp.bin";
    int a = 100000;

    if(metodo == 0)
    {
        ifstream arqTxt(pathTxt);

        char *buffer = new char[a];

        if(arqTxt.is_open()){
            while(!arqTxt.eof()){
                arqTxt.read(buffer, a);
                txt += buffer;
            }
            delete [] buffer;
        }

        else 
            cerr << "Erro ao tentar abrir o arquivo .txt" << endl;


        HuffmanCoding* teste = new HuffmanCoding;
        teste->contabiliza_Frequencia_string(txt);
        teste->preenche_lista_prioridade();
        // teste->imprime_lista_prioridade();
        
        NoHuff* no = teste->create_arvore_huffman();
        teste->preenche_Dicionario();
        // teste->impressao_dicionario();

        string comp = teste->comprime(txt);
        string dicionario = teste->retornaDicionarioArq();

        fstream arqBin(pathBin);

        if(arqBin.is_open()){
            arqBin.write(reinterpret_cast<const char *>(comp.c_str()), comp.length());
            arqBin.write(reinterpret_cast<const char *>(dicionario.c_str()), dicionario.length());
        }

        else
            cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
    }
}

void descomprime(int metodo)
{
    string txt = "";
    string dic = "";
    string pathBin = path + "reviewsComp.bin";
    string pathTxt = path + "reviewsDesc.txt";
    bool aux = true;

    int a = 100000;

    if(metodo == 0)
    {
        ifstream arqBin(pathBin);

        string line;

        if(arqBin.is_open()){
            while(getline(arqBin, line))
            {
                if(aux){
                    txt = line;
                    aux = false;
                }
                else
                    dic += line;
            }
        cout << dic << endl;
        }

        else 
            cerr << "Erro ao tentar abrir o arquivo .bin" << endl;

        HuffmanCoding* teste = new HuffmanCoding;

        teste->adicionaNovaLista(dic);
        teste->preenche_lista_prioridade();
        // teste->imprime_lista_prioridade();

        NoHuff* no = teste->create_arvore_huffman();
        teste->preenche_Dicionario();

        string descomp = teste->descomprime(txt);

        fstream arqTxt(pathTxt);

        if(arqTxt.is_open()){
            arqTxt << descomp;
        }

        else
            cerr << "Erro ao tentar abrir o arquivo .txt" << endl;
    }
}

int main(int argc, char **argv)
{
    int opcao = 1;
    int methodId;

    if(argc == 2)
        path = argv[1];
    
    // cout << "Digite a pasta onde o arquivo binario deve estar: " << endl;
    // getline(cin, path);

    descomprime(0);

    File *ratings = new File(path);

    ratings->createBinary(path);
    while (opcao != 4)
    {
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

            do
            {
                cout << "Digite qual metodo de ordenacao sera utilizado:" << endl;
                cout << "[0] Merge Sort" << endl;
                cout << "[1] Quick Sort" << endl;
                cout << "[2] Bucket Sort" << endl;
                cout << "[3] Retornar ao menu anterior" << endl;

                cin >> methodId;
                if (methodId < 0 || methodId > 3)
                {
                    cout << "Valor inválido: digite um valor entre 0 e 3..." << endl;
                }

            } while (methodId < 0 || methodId > 3);

            if (methodId != 3)
            {
                int linha;
                cout << "Digite o valor de n: \n";
                cin >> linha;

                ProductReview *vet;

                cout << "Registros a serem importados: " << linha << endl;
                vet = ratings->import(linha);


                sort(vet, linha, methodId);
            }

            break;
        }
        case 2:
            hashFunction();
            break;
        case 3:
            gerarSaida();
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