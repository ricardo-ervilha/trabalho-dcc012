#include <iostream>
#include <cstdlib>
#include "List.h"

using namespace std;

List::List(){
    primeiro = NULL;
    ultimo = NULL;
    n = 0;
}

List::~List(){
    NoList *p = primeiro;

    while(p != NULL){
        NoList *t = p->getProx();
        delete p;
        p = t;
    }
}

bool List::busca(unsigned long long val){
    NoList *p;
    for(p = primeiro; p != NULL; p = p->getProx()){
        if(p->getInfo() == val)
            return true;
    }

    return false;
}

void List::insereInicio(unsigned long long val){
    NoList* p = new NoList();
    p->setInfo(val);
    p->setProx(primeiro);

    primeiro  = p;

    n++;
    if(n == 1) ultimo = p;
}

void List::insereFinal(unsigned long long val){
    NoList* p = new NoList();
    p->setInfo(val);
    p->setProx(NULL);

    if(ultimo != NULL) ultimo->setProx(p);
    ultimo = p;

    n++;
    if(n == 1) primeiro = p;
}

int List::getN(){
    return n;
}

void List::imprimeLista(){
    NoList *p;
    
    for (p = primeiro; p != NULL; p = p->getProx())
        cout << p->getInfo() << " ";

    cout << endl;
}