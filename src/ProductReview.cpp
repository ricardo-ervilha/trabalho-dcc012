#include <iostream>
#include "ProductReview.h"

using namespace std;



ProductReview::ProductReview(string usuarioId, string produtoId, int carimboHora, int avaliacao){
    userId = usuarioId;
    productId = produtoId;
    timeStamp = carimboHora;
    rating = avaliacao;  
}


ProductReview::~ProductReview(){

}


void ProductReview::print(){
    cout << "{UserId: " << userId << ", ProductId: " << productId << ", TimeStamp: " << 
    timeStamp << ", Rating: " << timeStamp << "}" << endl;
}