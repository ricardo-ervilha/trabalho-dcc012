#include <iostream>
#include "HashProduct.h"
#include "File.h"
#include <cmath>
#include <cstring>
#include <cstdlib>


HashProduct::HashProduct(string path)
{
    this->path = path;
    Mlinha = 0;
    M = 0;
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

// djb2 hash
int HashProduct::h1(string productId)
{
    unsigned long hash = 5381;
    for (int i = 0; i < productId.length(); i++)
    {
        hash = ((hash << 5) + hash) + productId[i]; 
    }
    
    //return (hash % Mlinha) + 1; //se ela for h2 use isso
    return hash % M; //se ela for h1 use isso
}

//rolling hash
int HashProduct::h2(string productId)
{

    const char *vet = productId.c_str();
    unsigned long long soma = 0;

    int p = 11111;
    long int potencia = 1;

    int m = 1e9 + 9;

    for (int i = 0; i < productId.length(); i++)
    {
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
    return (soma % Mlinha) + 1; //se for h2 use isso
    //return soma % M; //se for h1 use isso
}

int HashProduct::sondagemDupla(string productid, int i)
{
    return (h1(productid) + i*h2(productid)) % M;
}

//retorna um booleano indicando se a inserção foi feita ou não. Se não for feita o programa se encerra.
bool HashProduct::insere(ProductReview produto)
{

    RegistroHash registro;

    registro.productId = produto.getProductId();
    registro.qtdReviews = 0;

    int index = sondagemDupla(produto.getProductId(), 0);

    if(table[index].productId == ""){
        //posição inserida não contém elementos ainda. Adiciono elemento.
        table[index] = registro;
        table[index].qtdReviews++;
        arqTabelaHash << produto.getProductId() << endl;
        return true;
    } else{
        //Colisão de dois tipos: mesmo productId ou productId diferente mas caiu no mesmo lugar.
        if(table[index].productId == produto.getProductId()){
            //se o produto é repetido.
            table[index].qtdReviews++; //Contabiliza a frequência.
            
            return true;
        }
        else{ 
            //produto B caiu por acidente no lugar onde já tem o A.
            int cont = 1;
            while(cont < M){
                index = sondagemDupla(produto.getProductId(), cont);
                
                if(table[index].productId == produto.getProductId()){
                    //Estava caminhando, achei posição ocupada e era igual ao meu productId.
                    table[index].qtdReviews++; 
                    
                    return true;
                }
                else if(table[index].productId == "") //achou lugar vazio
                {
                    //Estava procurando, e durante o caminho nunca encontrei alguem parecido comigo. 
                    //No entanto, achei posição vazia. Me insiro nela. Próxima pessoa que tentar ser inserida
                    //Com mesmo productId que o meu vai cair no if de cima.
                    

                    table[index]= registro;
                    table[index].qtdReviews++;
                    arqTabelaHash << produto.getProductId() << endl;
                    return true;
                }

                cont++;
            }
            //Por algum motivo não conseguiu inserir.
            return false;
        }
    }
}

//Acha quais os valores adequados de M e Mlinha para serem usados na sondagem dupla.
void HashProduct::adicionaPrimos(int n){
        if(n > 1 && n <= 10){
            M = 13;
            Mlinha = 11;
        }else if(n > 10 && n <= 100){
            M = 107;
            Mlinha = 97;
        }else if(n > 100 && n <= 250){
            M = 269;
            Mlinha =  241;
        }else if(n > 250 && n <= 500){
            M = 509;
            Mlinha = 491;
        }else if(n > 500 && n <= 1000){
            M = 1009;
            Mlinha = 997;
        }else if(n > 1000 && n <= 2500){
            M = 2503;
            Mlinha = 2477;
        }else if(n > 2500 && n <= 5000){
            M = 5003;
            Mlinha = 4999;   
        }else if(n > 5000 && n <= 10000){
            M = 10007;
            Mlinha = 9973;   
        }else if(n > 10000 && n <= 50000){
            M = 38053;
            Mlinha = 38047;   
        }else if(n > 50000 && n <= 100000){
            M = 67021;
            Mlinha = 67003;   
        }else if(n > 100000 && n <= 250000){
            M = 110051;
            Mlinha = 110039;   
        }else if(n > 250000 && n <= 500000){
            M = 165049;
            Mlinha = 165047;   
        }else if(n > 500000 && n <= 750000){
            M = 190093;
            Mlinha = 190063;   
        }else if(n > 750000 && n <= 1000000){
            M = 220057;
            Mlinha = 220021;   
        }else if(n > 1000000 && n <= 1500000){
            M = 270059;
            Mlinha = 270037;   
        }else if(n > 1500000 && n <= 2000000){
            M = 305033;
            Mlinha = 305029;   
        }else if(n > 2000000 && n <= 2500000){
            M = 340027;
            Mlinha = 340007;   
        }else if(n > 2500000){
            M = 490003;
            Mlinha = 490001;   
        }
}

RegistroHash *HashProduct::createTable(int n)
{
    adicionaPrimos(n); //acha os valores da tabela.

    File *arquivo = new File();

    table = new RegistroHash[M];
    inicializa(M);

    ProductReview *dadosImportados = arquivo->import(n);
    
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
}

void HashProduct::Troca(RegistroHash *list, int i, int j)
{
    RegistroHash aux;
    aux = list[i]; 
    list[i] = list[j];//troca o regitsro indice i
    list[j]= aux;//troca o registro indice j
    
}

int HashProduct::RandomPivo(int inicio, int fim)//Gera um pivô aleatório dentre os possíveis índices do vetor
{
    int posicao_pivo;
    posicao_pivo=inicio + (rand() % (fim-inicio+1));
    return posicao_pivo;
}

int HashProduct::Particiona(RegistroHash *list, int inicio, int fim)
{
    int posico_pivo = RandomPivo(inicio,fim);
    RegistroHash pivo = list[posico_pivo];
    int i = inicio, j = fim;

    while(true){
        while(list[i].qtdReviews > pivo.qtdReviews){
            
            i++;
        }
        while(list[j].qtdReviews < pivo.qtdReviews){
            j--;
        }
        if(i < j)
        {    
            Troca(list,i,j);
            i++;
            j--;
             
        } else{
            return j;
        }
        
    }
}

void HashProduct::QuickSortRec(RegistroHash *list, int inicio, int fim)
{
    if(inicio < fim)
    {
        int posicao = Particiona(list, inicio, fim);
        QuickSortRec(list, inicio, posicao); //Processo recursivo para particionar até que chegar a partições ordenadas(partições unicas) 
        QuickSortRec(list,posicao+1, fim); 
    }
}


void HashProduct::hashEtapa3(int p){

    RegistroHash *vet = new RegistroHash[M];

    //passa os valores da tabela para um vetor auxiliar
    int j = 0;
    for(int i = 0; i < M; i++){
        if(table[i].productId != ""){
            vet[j] = table[i];
            j++;
        }
    }
    
    //ordena os valores do vetor auxiliar 
    QuickSortRec(vet, 0, M-1);
    
    //imprime os p elementos pedidos pelo usuario;
    for(int i = 0; i < p; i++){
        cout << "Produto: " << vet[i].productId << " , Frequencia: " << vet[i].qtdReviews << endl;
    }

    delete [] vet; //deleta o ponteiro de registro hash que servia para imprimir os p elementos.
}