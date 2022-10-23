#ifndef PRODUCTREVIEW_H
#define PRODUCTREVIEW_H

using namespace std;

class ProductReview{

private:
    string userId; 
    string productId;
    string timeStamp;
    string rating;

public:
    ProductReview();
    ProductReview(string usuarioId, string produtoId, string avaliacao, string carimboHora);
    ~ProductReview();
    void print();
    string getProductId(); 
    string getUserId();
    string getTimeStamp();
    string getRating();
};

#endif