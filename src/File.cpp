#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include <time.h>
#include "File.h"
#include "Hash.h"

#define MAXCSV 7824482 //tamanho do arquivo CSV

using namespace std;

File::File(string path){
    maxU = 21;
    maxT = 10;
    this->path = path;
}

File::~File(){}

//Função para completar e padronizar o tamanho de cada string
string File::completeString(int n, string s){
    for(int i = 0; i < n; i++){
        s += '?';
    }
    return s;
}


//Função para tornar o buffer padronizado com valores '!' e facilitar na leitura dos dados do CSV
char* File::zeraVetor(int n, char* vet){

    for(int i=0; i<n; i++)
        vet[i] = '!';
    return vet;
}



//Alterar o cabeçalho para fazer aceitar uma string Path.
void File::createBinary(string& path)
{   
    ifstream existFile;

    this->path = path;

    string pathCsv = this->path + "ratings_Electronics.csv";
    string pathBinario = this->path + "ratings.bin";
    //const char* pathAuxBinario = pathBinario.c_str();
    //const char* pathAuxCsv = pathCsv.c_str();
    
    cout << "CAMINHO CSV: "<<pathCsv << endl;
    cout << "CAMINHO BINARIO: "<<pathBinario << endl;
    existFile.open(pathBinario);

    if(!existFile){
    cout << "Gerando arquivo binario..." << endl;
    int i = 0, val, a = 200000,  registro = 0, tam = a + 66; 
    time_t t_ini, t_fim; 

    ifstream arqCsv(pathCsv);
    fstream arq(pathBinario, ios::out | ios::binary);

    arqCsv.seekg (0, arqCsv.end);
    int length  = arqCsv.tellg();
    arqCsv.seekg (0, arqCsv.beg);

    char *buffer = new char [tam];

    char* cant = new char[2];
    cant[0] = ',';
    cant[1] = '\n';

    if (arqCsv.is_open())
    {
        if (arq.is_open())
        {
            t_ini = time(NULL);
            while (!arqCsv.eof())
            {
                //cout << "diferenca no inicio de bytes: " << length - arqCsv.tellg() << endl;
                if(length - arqCsv.tellg() < a)
                    a = length - arqCsv.tellg();
                //cout << "valor de a: " << a << endl;
                buffer = zeraVetor(tam, buffer);
                arqCsv.read(buffer, a);//lendo a bytes
                //cout << "Buffer no Inicio: ";
                //cout << buffer << endl;
                if(buffer[a-1] == '\n'){
                    //leu numero inteiro de registros
                    buffer[a] = '\0';
                }
                else if(buffer[a-1] != '!'){
                    int k = a;
                    while(buffer[k] == '!'){
                        k--;
                    }
                    buffer[k+1] = '\0';
                    //cout << "buffer atual: ";
                    //cout << buffer << endl; 
                    if(!arqCsv.eof()){
                        k = a;
                        char *aux = new char[1];
                        arqCsv.read(aux, 1);
                        while (aux[0] != '\n')
                        {
                            if (arqCsv.eof())
                                break;
                            buffer[k] = aux[0];
                            k++;
                            arqCsv.read(aux, 1);
                        }
                        buffer[k] = '\0';
                        //cout << "Buffer corrigido: ";
                        //cout << buffer << endl;
                        delete[] aux;
                    }
                }

                //ajustar o buffer para nao dar exceção


                char* c = strtok(buffer, cant);
 
                while (c)
                {
                    string linha(c);
                    if (i == 0)
                    {
                        if (linha.length() < maxU) //verifica se é menor que o tamanho maximo do userId
                        {
                            linha = completeString(maxU - linha.length(), linha);
                        }
                        arq.write(reinterpret_cast<const char* >(linha.c_str()), linha.length());
                    }
                    if (i == 3)
                    {
                        if (linha.length() < maxT) //verifica se é menor que o tamanho máximo do timeStamp
                        {
                            linha = completeString(10 - linha.length(), linha);
                        }
                        arq.write(reinterpret_cast<const char* >(linha.c_str()), linha.length());
                    }

                    if (i == 1 || i == 2)
                    {
                        arq.write(reinterpret_cast<const char *>(linha.c_str()), linha.length());
                        //if(i == 2){
                            //if(linha.length() != 3)
                                //cout << "rating de tamanho: "<<linha.length() << endl;
                        //}
                        //stringstream si(linha);
                        //si >> val;
                        //arq.write(reinterpret_cast<const char *>(&val), sizeof(int));
                    }

                    i++;
                    if (i == 4)
                    {
                        
                        //cout << registro << endl;
                        i = 0;
                    }

                    c = strtok(NULL, cant);
                
                }
            }
            delete[] cant;
            delete[] buffer;
            t_fim = time(NULL);
            cout << "Tempo(Usando a Time) : " << difftime(t_fim, t_ini) << endl;
        }
        else
            cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
    }
    else
        cerr << "Erro ao tentar abrir o arquivo .csv" << endl;

    cout << "Tamanho em bytes apos escrita: " << arq.tellp() << endl;
    arqCsv.close();
    arq.close();
    }

    else
        cout << "Arquivo binario ja existe. Acessando..." << endl;
}


void File::getReview(int i){
    ifstream arq(this->path + "ratings.bin", ios::binary);

    if(arq.is_open())
    {
        char userId[22], productId[11], ratings[3], timeStamp[11];
        arq.seekg(i*44);
        arq.read(userId, 21);

        for(int i = 0; i < 21; i++){
            if(userId[i] == '?')
            {
                userId[i] = '\0';
                break;
            }
        }
        userId[21] = '\0'; 
        cout << userId << ", ";
        arq.read(productId, 10);
        productId[10] = '\0';
        cout << productId << ", ";
        arq.read(ratings, 3);
        ratings[3] = '\0';
        cout << ratings << ", ";
        arq.read(timeStamp, 10);
        for(int i = 0; i < 11; i++){
            if(timeStamp[i] == '?')
            {
                timeStamp[i] = '\0';
                break;
            }
        }
        timeStamp[10] = '\0';
        cout << timeStamp << endl;
    }    

    arq.close();
}

ProductReview File::converteReview(int i){
    ifstream arq(this->path + "ratings.bin", ios::binary);

    char userId[22], productId[11], ratings[4], timeStamp[11];

    //cout <<"abc: " << this->pathFile<<endl;

    if(arq.is_open())
    {
        arq.seekg(i*44);
        arq.read(userId, 21);

        for(int i = 0; i < 21; i++){
            if(userId[i] == '?')
            {
                userId[i] = '\0';
                break;
            }
        }
        
        arq.read(productId, 10);
        productId[10] = '\0';
        
        arq.read(ratings, 3);
        ratings[3] = '\0';

        arq.read(timeStamp, 10);
        timeStamp[10] = '\0';

    } else{
        cout << "ERRO: Falha ao abrir o arquivo(converteReview).\n";
        exit(1);
    }

    arq.close();

    string usID(userId);
    string prodId(productId);
    string rat(ratings);
    string timeSt(timeStamp);

    ProductReview review(usID, prodId, ratings, timeStamp);

    return review;

}

unsigned long long llrand() {
    unsigned long long r = 0;

    for (int i = 0; i < 5; ++i) {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    return r & 0xFFFFFFFFFFFFFFFFULL;
}

ProductReview* File::import(int n){
    
    srand(time(NULL));

    ProductReview* listaReviews = new ProductReview[n];
    int p=n*0.65;
    if(n==1 && p==0)//Condição para evitar divisão por zero dentro da função Hash, permitindo a entrada no laço abaixo
    {
        p=1;
    }
    Hash* tabela = new Hash(p);
    unsigned long long chave = llrand()%MAXCSV;
    //cout<<"tamanho Chave "<< chave <<endl;
    for(int i = 0; i < n; i++){
        
        if(tabela->busca(chave)){
            while(tabela->busca(chave)){
                chave = llrand()%MAXCSV;
            }
        }
        
        listaReviews[i] = converteReview(chave);

        
        tabela->inserir(chave);

        chave = llrand()%MAXCSV;
        
    }
   return listaReviews;
}