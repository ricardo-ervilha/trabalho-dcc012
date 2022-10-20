#ifndef FILE_H
#define FILE_H

using namespace std;

class File{
private:
    int maxU; //maior quantidade de caracteres no userId
    string completeString(int n, string s);
    char* zeraVetor(int n, char* vet);
public:
    File();
    ~File();
    void makeBinaryFile();
    void getReview(int i);
};

#endif