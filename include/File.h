#ifndef FILE_H
#define FILE_H
#include "ProductReview.h"
#include <fstream>

using namespace std;

class File{
private:
    int maxU; //maior quantidade de caracteres no userId
    int maxT; //maior quantidade de caracteres no timeStamp
    string completeString(int n, string s);
    ProductReview converteReview(int i);
    char* zeraVetor(int n, char* vet);
    string path;//diretorio onde ficarão os arquivos binario e .csv
    ofstream chavesImport;
public:
    File(string path);
    ~File();
    void createBinary(string& path);
    void getReview(int i);
    ProductReview* import(int n); 
};

#endif