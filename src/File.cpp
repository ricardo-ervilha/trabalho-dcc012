#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <string.h>
#include <sstream>
#include <time.h>
#include "File.h"

using namespace std;

File::File(){
    maxU = 21;
}

File::~File(){}

string File::completeString(int n, string s){
    for(int i = 0; i < n; i++){
        s += '?';
    }
    return s;
}


char* File::zeraVetor(int n, char* vet){

    for(int i=0; i<n; i++)
        vet[i] = '!';
    return vet;
}

void File::makeBinaryFile()
{
    int i = 0, val, a = 200000,  registro = 0, tam = a + 66; //tam = a + 46 => a vale 123
    time_t t_ini, t_fim; 


    ifstream arqCsv("ratings_Electronics.csv");
    fstream arq("ratings.bin", ios::out | ios::binary);

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
                        if (linha.length() < maxU)
                        {
                            linha = completeString(maxU - linha.length(), linha);
                        }
                        arq.write(reinterpret_cast<const char* >(linha.c_str()), linha.length());
                    }
                    if (i == 1)
                    {
                        arq.write(reinterpret_cast<const char *>(linha.c_str()), linha.length());
                    }

                    if (i == 2 || i == 3)
                    {
                        stringstream si(linha);
                        si >> val;
                        arq.write(reinterpret_cast<const char *>(&val), sizeof(int));
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
            cout << "Tempo : " << difftime(t_fim, t_ini) << endl;
            cout << "registro: ";
            cout << registro << endl;
        }
        else
            cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;

    cout << "Tamanho em bytes apos escrita: " << arq.tellp() << endl;
    arqCsv.close();
    arq.close();
}


void File::getReview(int i){
    ifstream arq("ratings.bin", ios::binary);

    if(arq.is_open())
    {
        char userId[22], productId[11];
        int ratings, timeStamp;
        arq.seekg(i*39);
        arq.read(userId, 21);

        for(int i = 0; i < 22; i++){
            if(userId[i] == '?')
            {
                userId[i] = '\0';
                break;
            }
        }
        cout << userId << ", ";
        arq.read(productId, 10);
        productId[10] = '\0';
        cout << productId << ", ";
        arq.read(reinterpret_cast<char*>(&ratings), sizeof(int));
        cout << ratings << ".0, ";
        arq.read(reinterpret_cast<char*>(&timeStamp), sizeof(int));
        cout << timeStamp << endl;
    }    

    arq.close();
}

