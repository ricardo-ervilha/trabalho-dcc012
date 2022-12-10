#ifndef NOHUFF_H
#define NOHUFF_H

using namespace std;

class NoHuff{

private:
    NoHuff *esq;
    NoHuff *dir;
    NoHuff *prox;
    char caracter;
    int frequencia_caracter;
    
public:
    NoHuff() {};
    ~NoHuff() {};

    void setDir(NoHuff *dir)     {this->dir = dir;};
    void setEsq(NoHuff *esq)     {this->esq = esq;};
    void setProx(NoHuff *prox)    {this->prox = prox;};
    void setCaracter(char caracter)    {this->caracter = caracter;};
    void setFrequencia(int frequencia) {this->frequencia_caracter = frequencia;};

    NoHuff* getDir()     {return this->dir;};
    NoHuff* getEsq()     {return this->esq;};
    NoHuff* getProx()    {return this->prox;};
    char getCaracter()   {return this->caracter;};
    int getFrequencia()  {return this->frequencia_caracter;};
};

#endif