#ifndef PRODUCTREVIEW_H
#define PRODUCTREVIEW_H
#include <string>
using namespace std;

class ProductReview
{

private:
    string userId;
    string productId;
    string timeStamp;
    string rating;
    int localizacao;

public:
    ProductReview();
    ProductReview(string usuarioId, string produtoId, string avaliacao, string carimboHora, int local);
    ~ProductReview();
    void print();
    string getProductId();
    string getUserId();
    string getTimeStamp();
    string getRating();
    int getLocal();
};

#endif