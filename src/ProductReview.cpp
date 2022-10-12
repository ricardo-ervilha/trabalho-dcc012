#include <iostream>
#include "ProductReview.h"

using namespace std;



ProductReview::ProductReview(string usuarioId, string produtoId, int avaliacao, int carimboHora){
    userId = usuarioId;
    productId = produtoId;
    timeStamp = carimboHora;
    rating = avaliacao;  
}


ProductReview::~ProductReview(){

}


void ProductReview::print(){
    cout << "{UserId: " << userId << ", ProductId: " << productId << ", Rating: " << 
    rating << ", TimeStamp: " << timeStamp << "}" << endl;
}


string ProductReview::getProductId(){
    return productId;
} 
    

string ProductReview::getUserId(){
    return userId;
}


int ProductReview::getTimeStamp(){
    return timeStamp;
}

int ProductReview::getRating(){
    return rating;
}