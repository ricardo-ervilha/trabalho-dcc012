#ifndef PRODUCTREVIEW_H
#define PRODUCTREVIEW_H

using namespace std;

class ProductReview{

private:
    string userId; 
    string productId;
    int timeStamp;
    int rating;

public:
    ProductReview(string usuarioId, string produtoId, int avaliacao, int carimboHora);
    ~ProductReview();
    void print();
    string getProductId(); 
    string getUserId();
    int getTimeStamp();
    int getRating();
};

#endif