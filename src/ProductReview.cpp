#include <iostream>
#include "ProductReview.h"

using namespace std;

ProductReview::ProductReview(){
    
}

ProductReview::ProductReview(string usuarioId, string produtoId, string avaliacao, string carimboHora){
    userId = usuarioId;
    productId = produtoId;
    timeStamp = carimboHora;
    rating = avaliacao;  
}


ProductReview::~ProductReview(){}

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


string ProductReview::getTimeStamp(){
    return timeStamp;
}

string ProductReview::getRating(){
    return rating;
}