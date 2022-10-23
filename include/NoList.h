#ifndef NOLIST_H
#define NOLIST_H

class NoList{

private:
    unsigned long long info;
    NoList *prox;

public:
    NoList()                {};
    ~NoList()               {};
    unsigned long long getInfo()           { return info; };
    NoList* getProx()       { return prox; }  ;
    void setInfo(unsigned long long val)   { info = val; };
    void setProx(NoList* p) { prox = p; };
};


#endif