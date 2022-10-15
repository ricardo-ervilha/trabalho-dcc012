#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include "File.h"

using namespace std;

File::File(){
    maxU = 21; //esse nÃºmero foi obtido por meio de execucao
}

File::~File(){}

string File::completeString(int n, string s){
    for(int i = 0; i < n; i++)
    {
        s += '?';
    }
    return s;
}

void File::makeBinaryFile(){
    int i = 0, val;
    ifstream arqCsv("ratings_Electronics.csv");
    fstream arq("ratings.bin", ios::out | ios::binary);
    if(arqCsv.is_open()){
    if(arq.is_open())
    {
       string linha;
       string linhaAux;
       while(getline(arqCsv,linha)){
       stringstream aux(linha); //cria um objeto de stringstream o qual referencia a string linha
        while(getline(aux, linhaAux, ',')){ //realiza a separaÃ§Ã£o dos dados do arquivo utilizando a vÃ­rgula como separador
                if(i == 0){
                    if(linhaAux.length() < maxU){
                        linhaAux = completeString(maxU - linhaAux.length(), linhaAux);
                    }
                        arq.write(reinterpret_cast<const char*>(linhaAux.c_str()), linhaAux.length());
                }
                if(i == 1){
                    arq.write(reinterpret_cast<const char*>(linhaAux.c_str()), linhaAux.length());
                }

                if(i == 2 || i == 3){
                    stringstream si(linhaAux);
                    si >> val;
                    arq.write(reinterpret_cast<const char*>(&val), sizeof(int));
                }

                i++;

                if(i == 4){
                i = 0;
                }

                arq.write(reinterpret_cast<const char*>(linhaAux.c_str()), linhaAux.length());
        }
       }
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;

}
