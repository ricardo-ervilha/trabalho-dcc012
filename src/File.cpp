#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include <time.h>
#include "File.h"

using namespace std;


File::File()
{
    maxU = 21; // esse nÃºmero foi obtido por meio de execucao
}

File::~File() {}

void File::makeBinaryFile()
{
    int i = 0, val;
    time_t t_ini, t_fim; 
    ifstream arqCsv("ratings_Electronics.csv");
    fstream arq("ratings.bin", ios::out | ios::binary);
    if (arqCsv.is_open())
    {
        if (arq.is_open())
        {
            t_ini = time(NULL);
            string linha;
            string linhaAux;
            while (getline(arqCsv, linha))
            {
                stringstream aux(linha); // cria um objeto de stringstream o qual referencia a string linha
                while (getline(aux, linhaAux, ','))
                { // realiza a separacao dos dados do arquivo utilizando a virgula como separador
                    if (i == 0)
                    {
                        if (linhaAux.length() < maxU)
                        {
                            linhaAux = completeString(maxU - linhaAux.length(), linhaAux);
                        }
                        arq.write(reinterpret_cast<const char *>(linhaAux.c_str()), linhaAux.length());
                    }
                    if (i == 1)
                    {
                        arq.write(reinterpret_cast<const char *>(linhaAux.c_str()), linhaAux.length());
                    }

                    if (i == 2 || i == 3)
                    {
                        stringstream si(linhaAux);
                        si >> val;
                        arq.write(reinterpret_cast<const char *>(&val), sizeof(int));
                    }

                    i++;

                    if (i == 4)
                    {
                        i = 0;
                    }
                }
            }
            t_fim = time(NULL);
            cout << "Tempo : " << difftime(t_fim, t_ini) << endl;
        }
        else
            cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

void File::getRegistro(int i){
    ifstream arq("ratings.bin", ios::binary);

    if(arq.is_open())
    {
        string userId, productId;
        int ratings, timeStamp;
        arq.seekg((i)*39);
        //arq.read(userID, 21);
        //cout << userID << ", ";
        //cout << productID << ", ";
        arq.read(reinterpret_cast<char*>(&ratings), sizeof(int));
        cout << ratings << endl;
        arq.read(reinterpret_cast<char*>(&timeStamp), sizeof(int));
        cout << timeStamp << endl;
    }    

    arq.close();
}

