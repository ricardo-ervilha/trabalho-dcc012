#include <iostream>
#include "HashProduct.h"
#include "File.h"
#include <cmath>
#include <cstring>

#define M 73223

HashProduct::HashProduct(string path)
{
    this->path = path;
    
}

HashProduct::~HashProduct()
{
    delete table;
}

void HashProduct::inicializa(int n){

    for(int i = 0; i < n; i++){
        RegistroHash ini;
        ini.productId = "";
        ini.qtdReviews = 0;
        table[i] = ini;
    }
}


int HashProduct::converteStringInt(string productId)
{

    const char *vet = productId.c_str();
    unsigned long long soma = 0;

    // algoritmo de karp, o rabino.

    int p = 111111; // TODO: If the string s consists of only lower-case letters, then p = 31 is a good choice.

    long int potencia = 1;

    /*shall necessarily be a large prime since the probability of two keys
    colliding (producing the same hash) is nearly 1/m*/
    int m = 1e9 + 7;

    for (int i = 0; i < productId.length(); i++)
    {
        /*soma += (vet[i] -'a'+1) * (int) pow(CONST, (10 - (i+1)));
        soma = soma%M;
        cout << vet[i] << " ";
        cout << "pou: " << pow(CONST, (10 - (i+1))) << endl;*/

        // cout << "(" << soma << " + (" << (letra - 'A' + 1) << ") * " << potencia << ") % " << m << " = " << (soma + (letra - 'A' + 1) * potencia) % m << endl;
        if (vet[i] >= '0' && vet[i] <= '9')
        {
            soma = (soma + (vet[i] - '0' + 1) * potencia) % m;
        }
        else if (vet[i] >= 'a' && vet[i] <= 'z')
        {
            soma = (soma + (vet[i] - 'a' + 1) * potencia) % m;
        }
        else if (vet[i] >= 'A' && vet[i] <= 'Z')
        {
            soma = (soma + (vet[i] - 'A' + 1) * potencia) % m;
        }

        potencia = (potencia * p) % m;
    }
    // cout << "\n";
    // cout << "Valores de vet: " << soma << endl;
    return soma;
}

int HashProduct::funcaoHash(int chave)
{
    return chave % M;
}

void HashProduct::insere(ProductReview produto)
{

    RegistroHash registro;

    registro.productId = produto.getProductId();
    registro.qtdReviews = 0;


    int inteiroProduct = converteStringInt(produto.getProductId());
    int index = funcaoHash(inteiroProduct);

    if(table[index].productId == ""){
        table[index].qtdReviews++;
        table[index] = registro;
    } else{
        table[index].qtdReviews++;
    }
}

RegistroHash *HashProduct::createTable(int n)
{
    cout << "cde: " << this->path << endl;
    File *arquivo = new File(this->path);

    table = new RegistroHash[n];
    inicializa(n);

    ProductReview *dadosImportados = arquivo->import(n);

    for (int i = 0; i < n; i++)
    {
        
        insere(dadosImportados[i]);
    }

    delete[] dadosImportados;

    return table;
}

void HashProduct::printTable()
{

    /* for (int i = 0; i < M; i++)
    {
        // imprime somente se tiver algum valor na posição i da tabela
        if (table[i].productId.length())
        {
            cout << "[" << i << "]";

            cout << table[i].productId << " " << table[i].qtdReviews;
            cout << endl;
        }
    } */

    int maior = table[0].qtdReviews;
    for(int i = 1; i < M; i++){
        if(table[i].qtdReviews > maior)
            maior = table[i].qtdReviews;
    }

    float cont = 0;
    for(int i = 0; i < M; i++){
        if(table[i].productId != "")
            cont++;
    }

    cout << "Fator de carga: " << (cont/M) << endl;

    cout << "Maior " << maior << endl;
}