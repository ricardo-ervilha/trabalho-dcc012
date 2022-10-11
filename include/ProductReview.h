#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

using namespace std;

class ProductReview{

private:
    string userId; 
    string productId;
    int timeStamp;
    int rating;

public:
    ProductReview(string usuarioId, string produtoId, int carimboHora, int avaliacao);
    ~ProductReview();
    void print();
};

#endif