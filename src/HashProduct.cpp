#include <iostream>
#include "HashProduct.h"
#include "File.h"
#include <cmath>
#include <cstring>

#define CONST 10
#define M 97

HashProduct::HashProduct(){

}

HashProduct::~HashProduct(){
    delete table;
    
}

int HashProduct::converteStringInt(string productId){

    const char* vet = productId.c_str();
    unsigned long long soma = 0;

    //algoritmo de karp, o rabino.
    for(int i = 0; i < productId.length(); i++){
        soma += (vet[i] -'a'+1) * (int) pow(CONST, (10 - (i+1))); 
        soma = soma%M;
        cout << vet[i] << " ";
        cout << "pou: " << pow(CONST, (10 - (i+1))) << endl;
    }
    cout << "\n";
    cout << "Valores de vet: " << soma << endl;
    return soma;
}

int HashProduct::funcaoHash(int chave){
    return chave % M;
}



void HashProduct::insere(ProductReview produto){

    int inteiroProduct = converteStringInt(produto.getProductId());
    int index = funcaoHash(inteiroProduct);

    table[index] = produto;
}

ProductReview* HashProduct::createTable(int n){


    File* arquivo = new File();

    table = new ProductReview[100];

    ProductReview* dadosImportados = arquivo->import(n);

    for(int i = 0 ; i < n; i++){
        insere(dadosImportados[i]);
    }

    delete [] dadosImportados;

    return table;
}

void HashProduct::printTable(){
    
    for(int i = 0; i < M; i++){
        table[i].print();
        cout << endl;
    }

}