#include <iostream>
#include "HashProduct.h"
#include "File.h"
#include <cmath>
#include <cstring>

#define CONST 10
#define M 97

HashProduct::HashProduct()
{
}

HashProduct::~HashProduct()
{
    delete table;
}

int HashProduct::converteStringInt(string productId)
{

    const char *vet = productId.c_str();
    unsigned long long soma = 0;

    // algoritmo de karp, o rabino.

    int p = 31; // TODO: If the string s consists of only lower-case letters, then p = 31 is a good choice.

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

    int inteiroProduct = converteStringInt(produto.getProductId());
    int index = funcaoHash(inteiroProduct);

    table[index] = produto;
}

ProductReview *HashProduct::createTable(int n)
{
    File *arquivo = new File();

    table = new ProductReview[100];

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

    for (int i = 0; i < M; i++)
    {
        // imprime somente se tiver algum valor na posição i da tabela
        if (table[i].getProductId().length())
        {
            cout << "[" << i << "]";

            table[i].print();
            cout << endl;
        }
    }
}