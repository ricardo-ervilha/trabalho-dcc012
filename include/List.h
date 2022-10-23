#ifndef LIST_H
#define LIST_H

#include "NoList.h"

class List{

public:
    List();
    ~List();
    bool busca(unsigned long long val);
    void insereInicio(unsigned long long val);
    void insereFinal(unsigned long long val);
    int getN();
    void imprimeLista();

private:
    NoList* primeiro;
    NoList* ultimo;
    int n;

};


#endif