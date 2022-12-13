#include <iostream>
#include "ProductReview.h"

using namespace std;

ProductReview::ProductReview(){
    
}

ProductReview::ProductReview(string usuarioId, string produtoId, string avaliacao, string carimboHora, int local){
    userId = usuarioId;
    productId = produtoId;
    timeStamp = carimboHora;
    rating = avaliacao;
    localizacao = local;
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

int ProductReview::getLocal(){
    return localizacao;
}