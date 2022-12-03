#ifndef NOVP_H
#define NOVP_h
#include <iostream>

using namespace std;

class NoVP{
private:
    string id;
    bool color; //Black = False && Red = True
    NoVP *esq;
    NoVP *dir;
    int indexLoc; //índice de localização dentro do arquivo binário
    NoVP* pai;

public:
    NoVP(){this->color = true;};
    ~NoVP(){};
    string getInfo() { return id; };
    NoVP *getEsq() { return esq; };
    NoVP *getDir() { return dir; };
    NoVP *getPai() {return pai;};
    void setPai(NoVP* pai) {this->pai = pai;};
    bool getColor() {return color;};
    void setColor(bool color) {this->color = color;};
    void setInfo(string id) { this->id = id; };
    void setEsq(NoVP *esq) { this->esq = esq; };
    void setDir(NoVP *dir) { this->dir = dir; };
};

#endif