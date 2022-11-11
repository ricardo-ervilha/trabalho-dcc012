// #include <iostream>
// #include "HashProduct.h"
// #include "File.h"
// #include <cmath>
// #include <cstring>

// #define M 73223

// HashProduct::HashProduct(string path)
// {
//     this->path = path;
// }

// HashProduct::~HashProduct()
// {
//     delete[] table;
// }

// void HashProduct::inicializa(int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         RegistroHash ini;
//         ini.productId = "";
//         ini.qtdReviews = 0;
//         table[i] = ini;
//     }
// }

// /*
//     Cria uma tabela que irá armazenar n registros
// */
// RegistroHash *HashProduct::createTable(int n)
// {
//     File *arquivo = new File(this->path);

//     table = new RegistroHash[n];
//     chavesGeradas = new int[n];

//     // inicializa(n);

//     ProductReview *dadosImportados = arquivo->import(n);

//     arqChavesGeradas.open(this->path + "chaves.csv");
//     arqTabelaHash.open(this->path + "tabelaHash.csv");
//     arqTabelaHash << "Index,"
//                   << "Product"
//                   << ","
//                   << "Erro" << endl;
//     if (arqChavesGeradas.is_open() && arqTabelaHash.is_open())
//     {
//         arqChavesGeradas << "Chaves" << endl;
//         for (int i = 0; i < n; i++)
//         {
//             // this->insere(dadosImportados[i]);
//             this->insereProduto(dadosImportados[i]);
//         }
//     }

//     delete[] dadosImportados;
//     delete[] chavesGeradas;

//     arqChavesGeradas.close();
//     arqTabelaHash.close();

//     return table;
// }

// void HashProduct::insere(ProductReview produto)
// {
//     RegistroHash registro;

//     registro.productId = produto.getProductId();
//     registro.qtdReviews = 1;

//     int index = h2(produto.getProductId());

//     chavesGeradas[lastIndex++] = index; // salvar as chaves geradas  no vetor
//     arqChavesGeradas << index << endl;  // joga pro arquivo também

//     if (table[index].productId.empty())
//     {
//         table[index].qtdReviews = table[index].qtdReviews + 1;
//         table[index] = registro;
//     }
//     else
//     {
//         table[index].qtdReviews++;
//     }
// }

// void HashProduct::insereProduto(ProductReview produto)
// {
//     RegistroHash registro = {{produto.getProductId(), 0}};

//     int collisions = 0;
//     int index = h(produto.getProductId(), collisions);

//     // Fica no loop até que:
//     //  1 - Ache uma posição vazia
//     //  2 - Ache um produto com o mesmo productId
//     //  3 - O numero de colisões seja maior do que M
//     while (!table[index].productId.empty() && table[index].productId != produto.getProductId() && collisions < M)
//     {
//         index = h(table[index].productId, ++collisions);
//     }

//     // produto repetido
//     if (table[index].productId == produto.getProductId())
//     {
//         arqTabelaHash << index << "," << produto.getProductId() << endl;
//         table[index].qtdReviews++;
//     }
//     else if (collisions < M)
//     { // não encontrou produto repetido e ainda tem espaço na tabela
//         arqTabelaHash << index << "," << produto.getProductId() << endl;
//         table[index] = registro;
//     }
//     else
//     {
//         arqTabelaHash << index << "," << table[index].productId << ",ERRO!" << endl;
//         cout << " Tabela cheia!" << endl;
//         cout << "Colisoes: " << collisions << endl;
//         exit(1);
//     }
// }

// // Implementação usando sondagem dupla
// int HashProduct::h(string productId, int collisions)
// {
//     return (h1(productId) + (++collisions) * h2(productId)) % M;
// }
// int HashProduct::h1(string productId)
// {
//     unsigned long long soma = 0;
//     long int potencia = 1;
//     int m = 1e9 + 7;
//     int p = 31;
//     const char *vet = productId.c_str();

//     for (int i = 0; i < productId.length(); i++)
//     {
//         soma = (soma + asciiValue(vet[i]) * potencia) % m;
//         potencia = (potencia * p) % m;
//     }

//     return soma % M;
// }

// // djb2 hash
// int HashProduct::h2(string productId)
// {
//     unsigned long hash = 5381;
//     for (int i = 0; i < productId.length(); i++)
//     {
//         hash = ((hash << 5) + hash) + productId[i]; /* hash * 33 + c */
//     }

//     return hash % M;
// }

// int HashProduct::asciiValue(char c)
// {
//     if (c >= '0' && c <= '9')
//     {
//         return (c - '0' + 1);
//     }
//     else if (c >= 'a' && c <= 'z')
//     {
//         return (c - 'a' + 1);
//     }
//     else if (c >= 'A' && c <= 'Z')
//     {
//         return (c - 'A' + 1);
//     }
//     else
//     {
//         cout << "Character inválido.." << endl;
//         return 1;
//     }
// }

// int HashProduct::converteStringInt(string productId)
// {

//     const char *vet = productId.c_str();
//     unsigned long long soma = 0;

//     // algoritmo de karp, o rabino.

//     int p = 111111; // TODO: If the string s consists of only lower-case letters, then p = 31 is a good choice.

//     long int potencia = 1;

//     /*shall necessarily be a large prime since the probability of two keys
//     colliding (producing the same hash) is nearly 1/m*/
//     int m = 1e9 + 7;

//     for (int i = 0; i < productId.length(); i++)
//     {
//         /*soma += (vet[i] -'a'+1) * (int) pow(CONST, (10 - (i+1)));
//         soma = soma%M;
//         cout << vet[i] << " ";
//         cout << "pou: " << pow(CONST, (10 - (i+1))) << endl;*/

//         // cout << "(" << soma << " + (" << (letra - 'A' + 1) << ") * " << potencia << ") % " << m << " = " << (soma + (letra - 'A' + 1) * potencia) % m << endl;
//         if (vet[i] >= '0' && vet[i] <= '9')
//         {
//             soma = (soma + (vet[i] - '0' + 1) * potencia) % m;
//         }
//         else if (vet[i] >= 'a' && vet[i] <= 'z')
//         {
//             soma = (soma + (vet[i] - 'a' + 1) * potencia) % m;
//         }
//         else if (vet[i] >= 'A' && vet[i] <= 'Z')
//         {
//             soma = (soma + (vet[i] - 'A' + 1) * potencia) % m;
//         }

//         potencia = (potencia * p) % m;
//     }
//     // cout << "\n";
//     cout << "ConvertString: " << soma << endl;

//     return soma;
// }

// int HashProduct::funcaoHash(int chave)
// {
//     return chave % M;
// }

// void HashProduct::printTable()
// {
//     /*for (int i = 0; i < M; i++)
//     {
//         // imprime somente se tiver algum valor na posição i da tabela
//         if (table[i].productId.length())
//         {
//             cout << "[" << i << "]";
//             cout << table[i].productId << " " << table[i].qtdReviews;
//             cout << endl;
//         }
//     }*/

//     int maior = 0;
//     ofstream arqQtReviews(this->path + "qtdReviews.csv");
//     for (int i = 0; i < M; i++)
//     {
//         if (!table[i].productId.empty())
//         {
//             arqQtReviews << table[i].qtdReviews << "," << table[i].productId << endl;
//             if (table[i].qtdReviews > maior)
//                 maior = table[i].qtdReviews;
//         }
//     }

//     arqQtReviews.close();

//     float cont = 0;
//     for (int i = 0; i < M; i++)
//     {
//         if (table[i].productId != "")
//             cont++;
//     }

//     cout << "Fator de carga: " << (cont / M) << endl;
//     cout << "Maior " << maior << endl;
// }

#include <iostream>
#include "HashProduct.h"
#include "File.h"
#include <cmath>
#include <cstring>
#include <cstdlib>

//testar para 100000 -> 73237 e 71147

#define M 10321

#define Mlinha 10313

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

int HashProduct::h2(string productId){
    const char *vet = productId.c_str();
    unsigned long long soma = 0;

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
    
    return (soma % Mlinha) + 1;
}


int HashProduct::h1(string productId)
{

    const char *vet = productId.c_str();
    unsigned long long soma = 0;

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

    return soma % M;
}

int HashProduct::sondagemDupla(string productid, int i)
{
    return (h1(productid) + i*h2(productid)) % M;
}

bool HashProduct::insere(ProductReview produto)
{

    RegistroHash registro;

    registro.productId = produto.getProductId();
    registro.qtdReviews = 0;

    int index = sondagemDupla(produto.getProductId(), 0);

    if(table[index].productId == ""){
        //posição inserida não contém elementos ainda.
        table[index] = registro;
        table[index].qtdReviews++;
        arqTabelaHash << index << "," << produto.getProductId() << endl;
        return true;
    } else{
        //colisão.
        if(table[index].productId == produto.getProductId()){
            //se o produto é repetido.
            table[index].qtdReviews++; //Contabiliza a frequência.
            cout << "Repetiu\n";
            return true;
        }
        else{ 
            //produto B caiu por acidente no lugar onde já tem o A.
            int cont = 1;
            while(cont < M){
                index = sondagemDupla(produto.getProductId(), cont);
                if(table[index].productId == "") //achou lugar vazio
                {
                    cout << "Colisão tratada." << endl;
                    table[index]= registro;
                    table[index].qtdReviews++;
                    arqTabelaHash << index << "," << produto.getProductId() << endl;
                    return true;
                }
                cont++;
            }
            return false;
        }
    }
}

RegistroHash *HashProduct::createTable(int n)
{
    cout << "cde: " << this->path << endl;
    File *arquivo = new File(this->path);

    table = new RegistroHash[M];
    inicializa(M);

    ProductReview *dadosImportados = arquivo->import(n);

    arqTabelaHash.open(this->path + "tabelaHash.csv");
    
    arqTabelaHash << "Index,"
                   << "Product"
                   << ","
                 << "Erro" << endl;
    
    if (arqTabelaHash.is_open()){
        for (int i = 0; i < n; i++)
        {
            bool result = insere(dadosImportados[i]);
            if (result == false)
            {
                cout << "Falha na inserção.\n";
                exit(1);
            }
        }
    }
    

    delete[] dadosImportados;

    return table;
}

void HashProduct::printTable()
{

    for (int i = 0; i < M; i++)
    {
        // imprime somente se tiver algum valor na posição i da tabela
        if (table[i].productId.length())
        {
            cout << "[" << i << "]";

            cout << table[i].productId << " " << table[i].qtdReviews;
            cout << endl;
        }
    } 

    int maior = table[0].qtdReviews;
    
    int sum = table[0].qtdReviews;
    for(int i = 1; i < M; i++){
        if(table[i].qtdReviews > maior)
            maior = table[i].qtdReviews;
        
        sum+= table[i].qtdReviews;
    }

    float cont = 0;
    for(int i = 0; i < M; i++){
        if(table[i].productId != "")
            cont++;
    }

    cout << "Valor de sum: " << sum << endl;
    cout << "Valor de cont: " << cont << endl;
    cout << "Fator de carga: " << (cont/M) << endl;
    cout << "Maior numero de colisões encontrado: " << maior << endl;
}