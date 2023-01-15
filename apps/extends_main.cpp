#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <time.h>
#include "ProductReview.h"
#include <chrono>
#include "Hash.h"
#include <fstream>
#include "HuffmanCoding.h"
#include "LZ77Coding.h"
#include "LZWCoding.h"
#include "ArvoreVP.h"
#include "ArvoreB.h"


#define maxU  21
#define maxT  10
#define MAXCSV 7824482 

using namespace std;
using namespace std::chrono;


/*
Main que está sendo usada para testar as implementações referentes a segunda parte do trabalho.
*/

// Variáveis globais
string path;
NoHuff *raiz;

//Parte referente aos métodos para manipulação do binário, importação de dados e obtenção de reviews do arquivo.

string completeString(int n, string s){
    for(int i = 0; i < n; i++){
        s += '?';
    }
    return s;
}

char* zeraVetor(int n, char* vet){

    for(int i=0; i<n; i++)
        vet[i] = '!';
    return vet;
}

void createBinary(string& path_linha)
{   
    ifstream existFile;

    string pathCsv = path_linha + "ratings_Electronics.csv";
    string pathBinario = path_linha + "ratings.bin";
    
    existFile.open(pathBinario);

    if (!existFile)
    {
        cout << "Gerando arquivo binario..." << endl;
        int i = 0, val, a = 200000, registro = 0, tam = a + 66;
        time_t t_ini, t_fim;

        ifstream arqCsv(pathCsv);
        fstream arq(pathBinario, ios::out | ios::binary);

        arqCsv.seekg(0, arqCsv.end);
        int length = arqCsv.tellg();
        arqCsv.seekg(0, arqCsv.beg);

        char *buffer = new char[tam];

        //caracteres que devem ser usados para split.
        char *cant = new char[2];
        cant[0] = ',';
        cant[1] = '\n';

        if (arqCsv.is_open())
        {
            if (arq.is_open())
            {
                t_ini = time(NULL);
                while (!arqCsv.eof())
                {
                    if (length - arqCsv.tellg() < a)
                        a = length - arqCsv.tellg();

                    buffer = zeraVetor(tam, buffer);
                    arqCsv.read(buffer, a); // lendo a bytes

                    if (buffer[a - 1] == '\n')
                    {
                        // leu numero inteiro de registros
                        buffer[a] = '\0';
                    }
                    else if (buffer[a - 1] != '!')
                    {
                        
                        // ajustar o buffer para nao dar exceção
                        int k = a;
                        while (buffer[k] == '!')
                        {
                            k--;
                        }
                        buffer[k + 1] = '\0';
                        if (!arqCsv.eof())
                        {
                            k = a;
                            char *aux = new char[1];
                            arqCsv.read(aux, 1);
                            while (aux[0] != '\n')
                            {
                                if (arqCsv.eof())
                                    break;
                                buffer[k] = aux[0];
                                k++;
                                arqCsv.read(aux, 1);
                            }
                            buffer[k] = '\0';
                            delete[] aux;
                        }
                    }

                    char *c = strtok(buffer, cant);

                    while (c)
                    {
                        string linha(c);
                        if (i == 0)
                        {
                            if (linha.length() < maxU) // verifica se é menor que o tamanho maximo do userId
                            {
                                linha = completeString(maxU - linha.length(), linha);
                            }
                            arq.write(reinterpret_cast<const char *>(linha.c_str()), linha.length());
                        }
                        if (i == 3)
                        {
                            if (linha.length() < maxT) // verifica se é menor que o tamanho máximo do timeStamp
                            {
                                linha = completeString(10 - linha.length(), linha);
                            }
                            arq.write(reinterpret_cast<const char *>(linha.c_str()), linha.length());
                        }

                        if (i == 1 || i == 2)
                        {
                            arq.write(reinterpret_cast<const char *>(linha.c_str()), linha.length());
                        }

                        i++;
                        if (i == 4)
                        {
                            i = 0;
                        }

                        c = strtok(NULL, cant);
                    }
                }
                delete[] cant;
                delete[] buffer;
                
                high_resolution_clock::time_point inicio = high_resolution_clock::now();
                high_resolution_clock::time_point fim = high_resolution_clock::now();
                auto duracao = duration_cast<duration<double, std::nano>>(fim - inicio);
                std::cout << "Tempo para gerar o binario: " << duracao.count() * pow(10, -9) << std::endl;
            }
            else
                cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
        }
        else
            cerr << "Erro ao tentar abrir o arquivo .csv" << endl;

        cout << "Tamanho em bytes apos escrita: " << arq.tellp() << endl;
        arqCsv.close();
        arq.close();
    }
    else
        cout << "Arquivo binario ja existe. Acessando..." << endl;
}

void getReview(int i){
    ifstream arq(path + "ratings.bin", ios::binary);

    if(arq.is_open())
    {
        char userId[22], productId[11], ratings[4], timeStamp[11];
        arq.seekg(i*44); //Cada registro contém 44 bytes por padrão.

        arq.read(userId, 21);

        for(int i = 0; i < 21; i++){
            if(userId[i] == '?')
            {
                userId[i] = '\0';
                break;
            }
        }
        userId[21] = '\0'; 
        cout << userId << ", ";

        arq.read(productId, 10);
        productId[10] = '\0';
        cout << productId << ", ";

        arq.read(ratings, 3);
        ratings[3] = '\0';
        cout << ratings << ", ";

        arq.read(timeStamp, 10);
        for(int i = 0; i < 11; i++){
            if(timeStamp[i] == '?')
            {
                timeStamp[i] = '\0';
                break;
            }
        }
        timeStamp[10] = '\0';
        cout << timeStamp << endl;
    }    

    arq.close();
}

ProductReview converteReview(int i){
    string filePath = path + "ratings.bin";
    ifstream arq(filePath, ios::binary);

    char userId[22], productId[11], ratings[4], timeStamp[11];

    if(arq.is_open())
    {
        arq.seekg(i*44);
        arq.read(userId, 21);

        for(int i = 0; i < 21; i++){
            if(userId[i] == '?')
            {
                userId[i] = '\0';
                break;
            }
        }
        userId[21] = '\0';
        arq.read(productId, 10);
        productId[10] = '\0';
        
        arq.read(ratings, 3);
        ratings[3] = '\0';

        arq.read(timeStamp, 10);
        timeStamp[10] = '\0';

    } else{
        cout << "ERRO: Falha ao abrir o arquivo(converteReview).\n";
        cout <<"Caminho: "<<filePath<<endl;
        exit(1);
    }

    arq.close();

    //converter os chars de volta para string
    string usID(userId);
    string prodId(productId);
    string rat(ratings);
    string timeSt(timeStamp);

    //gera o registro
    ProductReview review(usID, prodId, ratings, timeStamp, i);

    return review;

}

//Função para gerar os indices aleatorios que serão pulados no arquivo binario pela seekg.
unsigned long long random_numbers() {
    unsigned long long r = 0;

    for (int i = 0; i < 5; ++i) {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    return r & 0xFFFFFFFFFFFFFFFFULL;
}

ProductReview* import(int n){

    srand(time(NULL));
    
    ProductReview *listaReviews = new ProductReview[n];
    int p = n;
    
    if (n == 1 && p == 0) // Condição para evitar divisão por zero dentro da função Hash, permitindo a entrada no laço abaixo
    {
        p = 1;
    }
    
    Hash *tabela = new Hash(p);
    unsigned long long chave = random_numbers() % MAXCSV;
    

        for (int i = 0; i < n; i++)
        {

            if (tabela->busca(chave))
            {
                while (tabela->busca(chave))
                {
                    chave = random_numbers() % MAXCSV;
                }
            }

            ProductReview review = converteReview(chave);

            listaReviews[i] = review;

            tabela->inserir(chave);

            chave = random_numbers() % MAXCSV;
        }
    
    
    return listaReviews;
}

//Fim


//Método auxiliar para calcular o tamanho da string antes e pós-compressão.
int computaTamanhoString(string txt, bool flag){
    if(flag){
        return txt.length() * 8; //True -> string antes de comprimir
    } else{
        return txt.length(); //False -> string depois de comprimir
    }
}

//Método auxiliar para concatenação da string dos registros
string concatenaRegistros(ProductReview* registros, int n){

    string texto = "";

    for(int i = 0; i < n; i++){
        texto += (registros[i].getProductId() + registros[i].getUserId() + registros[i].getTimeStamp() + registros[i].getRating());
    }

    return texto;
}

//Comprime uma string qualquer passsada como parâmetro.
string comprime(string str, int metodo){

    if (metodo == 0)
    {
        // Compressão do Huffman
        HuffmanCoding *huff = new HuffmanCoding();
        huff->contabiliza_Frequencia_string(str);
        huff->preenche_lista_prioridade();
        huff->create_arvore_huffman();
        huff->preenche_Dicionario();
        char **dicionario = huff->getDicionario();
        raiz = huff->getInicioLista();
        string comp = "";
        for (int i = 0; i < str.length(); i++)
                comp += dicionario[str[i]];
        return comp;
    }
    else if (metodo == 1)
    {
        //Compressao LZ77
        string comp = "";
        LZ77Coding *lz77 = new LZ77Coding();
        comp = lz77->Comprime(str);
        return comp;
    }
    else
    {
        //Compressao LZW
        string comp = "";
        LZWCoding *lzw = new LZWCoding();
        comp = lzw->Comprime(str);
        return comp;
    }
}

string auxDescomprime(NoHuff *p, string str, string descomp, int i)
{
    if(p->getEsq() == NULL && p->getDir() == NULL){ //eh folha
        
        descomp += p->getCaracter();

        if(i < str.length())
            return auxDescomprime(raiz, str, descomp, i);

        else
            return descomp;
    }

    if(str[i] == '0')
        return auxDescomprime(p->getEsq(), str, descomp, i+1);
    else
        return auxDescomprime(p->getDir(), str, descomp, i+1);
}


//Descomprime uma string qualquer passsada como parâmetro.
string descomprime(string str, int metodo){
    
    if (metodo == 0)
    {
        // Descompressão do Huffman
        string descomp = "";
    
        return auxDescomprime(raiz, str, descomp, 0);
        
    }
    else if (metodo == 1)
    {
        //Descompressao LZ77
        string descomp = "";
        LZ77Coding *lz77 = new LZ77Coding();
        descomp = lz77->Descomprime(str);
        return descomp;
    }
    else
    {
        //Descompressao LZW
        string descomp = "";
        LZWCoding *lzw = new LZWCoding();
        descomp = lzw->Descomprime(str);
        return descomp;
    }
}

// Comprime um arquivo.
void comprime(int metodo)
{
    string txt = "";
    string pathTxt = path + "reviewsOrig.txt";
    string pathBin = path + "reviewsComp.bin";
    int a = 100000;

    ifstream arqTxt(pathTxt);

    char *buffer = new char[a];

    if (arqTxt.is_open())
    {

        while (!arqTxt.eof())
        {
            arqTxt.read(buffer, a);
            txt += buffer;
        }
        delete[] buffer;
    }
    else
        cerr << "Erro ao tentar abrir o arquivo .txt" << endl;

    arqTxt.close();

    if (metodo == 0)
    {
        //Compreessao Huffman
        
        HuffmanCoding *huff = new HuffmanCoding();
        huff->contabiliza_Frequencia_string(txt);
        huff->preenche_lista_prioridade();

        NoHuff *no = huff->create_arvore_huffman();
        huff->preenche_Dicionario();

        string comp = comprime(txt, 0);
        string dicionario = huff->retornaDicionarioArq();

        fstream arqBin(pathBin);

        if (arqBin.is_open())
        {
            arqBin.write(reinterpret_cast<const char *>(comp.c_str()), comp.length());
            arqBin.write(reinterpret_cast<const char *>(dicionario.c_str()), dicionario.length());
        }

        else
            cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
        arqBin.close();
    }
    else if (metodo == 1)
    {
        //Compressao LZ77
        string comp = comprime(txt, 1);
        fstream arqBin(pathBin);

        if (arqBin.is_open())
            arqBin.write(reinterpret_cast<const char *>(comp.c_str()), comp.length());
        else
            cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
        arqBin.close();
    }
    else
    {
        //Compressao LZW
        string comp = comprime(txt, 2);
        fstream arqBin(pathBin);

        if (arqBin.is_open())
            arqBin.write(reinterpret_cast<const char *>(comp.c_str()), comp.length());
        else
            cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
        arqBin.close();
    }
}

//Descomprime um arquivo.
void descomprime(int metodo)
{
    string txt = "";
    string dic = "";
    string pathBin = path + "reviewsComp.bin";
    string pathTxt = path + "reviewsDesc.txt";
    bool aux = true;

    ifstream arqBin(pathBin);

    string line;

    if(arqBin.is_open())
    {
        while(getline(arqBin, line))
        {
            if(aux){
                txt = line;
                aux = false;
            }
            else
                dic += line;
        }
    cout << dic << endl;
    }
    else 
        cerr << "Erro ao tentar abrir o arquivo .bin" << endl;

    arqBin.close();
    if(metodo == 0)
    {
        //Descompressao Huffman
        
        HuffmanCoding *huff = new HuffmanCoding();

        huff->adicionaNovaLista(dic);
        huff->preenche_lista_prioridade();
        // teste->imprime_lista_prioridade();

        NoHuff* no = huff->create_arvore_huffman();
        huff->preenche_Dicionario();

        string descomp = huff->descomprime(txt);

        fstream arqTxt(pathTxt);

        if(arqTxt.is_open()){
            arqTxt << descomp;
        }
        else
            cerr << "Erro ao tentar abrir o arquivo .txt" << endl;
        
        arqTxt.close();
    }else if (metodo == 1)
    {
        //Descompressao LZ77

        LZ77Coding *lz77 = new LZ77Coding();

        string descomp = lz77->Descomprime(txt);

        fstream arqTxt(pathTxt);

        if(arqTxt.is_open()){
            arqTxt << descomp;
        }
        else
            cerr << "Erro ao tentar abrir o arquivo .txt" << endl;
        
        arqTxt.close();

    }
    else
    {
        //Descompressao LZW
        LZWCoding *lzw = new LZWCoding();

        string descomp = lzw->Descomprime(txt);

        fstream arqTxt(pathTxt);

        if(arqTxt.is_open()){
            arqTxt << descomp;
        }
        else
            cerr << "Erro ao tentar abrir o arquivo .txt" << endl;
        
        arqTxt.close();
    }
}

template<typename T>
void zera_vet(T *vet, int n){
    for(int i = 0; i < n; i++)
        vet[i] = 0;
}

void gerarSaidaCompressao(){
    int n;
    cout << "Qual a quantidade de registros que serao concatenados durante as execucoes?" << endl;
    cin >> n;

    int *tam_Inicio = new int[9];
    zera_vet(tam_Inicio, 9);
    int *tam_Final = new int[9];
    zera_vet(tam_Final, 9);

    ofstream saida; // variável para gerar a saída com as estatísticas
    saida.open("saida_compressao.txt");

    for(int i = 0; i < 3; i++){
        
        for(int j = 0; j < 3; j++){
            ProductReview* registros = new ProductReview[n];
        
            registros = import(n);

            string texto = concatenaRegistros(registros, n); //Função para concatenar os registros
         
            if(i == 0){
                //Huffman
                tam_Inicio[3*i + j] = computaTamanhoString(texto, true);
                
                string code = comprime(texto, 0);  
                
                tam_Final[3*i + j] = computaTamanhoString(code, false);
            } else if(i == 1){
                tam_Inicio[3*i + j] = computaTamanhoString(texto, false);
                
                string code = comprime(texto, 1);  
                
                tam_Final[3*i + j] = computaTamanhoString(code, false);
            } else{
                //LZW
            }
            
            delete [] registros;
        }
    }

    float *taxas_compressao = new float[9];
    zera_vet(taxas_compressao, 9);
    float media = 0;

    saida << "*************************Dados do Huffman*************************" << endl;
    saida << "Iteração\tTamanho Inicial\tTamanho Final\tTaxa de compressao" << endl;
    for(int i = 0; i < 3; i++){
        taxas_compressao[i] = (float)(tam_Inicio[i] - tam_Final[i])/tam_Inicio[i];
        media += taxas_compressao[i];
        saida << i << "\t\t\t" << tam_Inicio[i] << "\t\t\t" << tam_Final[i] << "\t\t\t" << taxas_compressao[i] << endl;
    }
    saida << "Media das taxas de compressao: " << media/(3.0) <<endl;

    media = 0;
    saida << "*************************Dados do LZ77*************************" << endl;
    saida << "Iteração\tTamanho Inicial\tTamanho Final\tTaxa de compressao" << endl;
    for(int i = 3; i < 6; i++){
        taxas_compressao[i] = (float)(tam_Inicio[i] - tam_Final[i])/tam_Inicio[i];
        media += taxas_compressao[i];
        saida << i << "\t\t\t" << tam_Inicio[i] << "\t\t\t" << tam_Final[i] << "\t\t\t" << taxas_compressao[i] << endl;
    }
    saida << "Media das taxas de compressao: " << media/(3.0) <<endl;

    media = 0;
    saida << "*************************Dados do LZW*************************" << endl;
    saida << "Iteração\tTamanho Inicial\tTamanho Final\tTaxa de compressao" << endl;
    for(int i = 6; i < 9; i++){
        taxas_compressao[i] = (float)(tam_Inicio[i] - tam_Final[i])/tam_Inicio[i];
        media += taxas_compressao[i];
        saida << i << "\t\t\t" << tam_Inicio[i] << "\t\t\t" << tam_Final[i] << "\t\t\t" << taxas_compressao[i] << endl;
    }
    saida << "Media das taxas de compressao: " << media/(3.0) <<endl;

    saida.close();
}

void gerarSaidaEstruturasBalanceadas()
{
    int n = 10000;
    int b = 100;
    int index;

    int *comp_Insert = new int[3];
    int *comp_Search = new int[3];
    double *time_Insert = new double[3];
    double *time_Search = new double[3];

    ProductReview *list;
    ArvoreVP *tree;
    ArvoreB *arv;

    ofstream saida; // variável para gerar a saída com as estatísticas
    saida.open("saida_estruturasBalanceadas.txt");

    
    cout << "Estatisticas da Arvore Vermelho-Preto" << endl;
    saida << "\t\t\t\t\t\tEstatisticas da Arvore Vermelho-Preto" << endl;
    saida << "Comparacoes de Insercao\t"
          << "Tempo de insercao(s)\t\t"
          << "Comparacoes de busca\t\t"
          << "Tempo de busca" << endl;

    for (int i = 0; i < 3; i++)
    {
        list = import(n);
        tree = new ArvoreVP();

        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::chrono::duration<double> elapsed_seconds;

        start = std::chrono::system_clock::now();
        for (int j = 0; j < n; j++)
        {
            tree->insere(&list[j]);
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        time_Insert[i] = elapsed_seconds.count();

        comp_Insert[i] = tree->getComparacaoIn();

        start = std::chrono::system_clock::now();
        for (int j = 0; j < b; j++)
        {
            index = random_numbers() % n;
            tree->busca(list[index].getUserId(), list[index].getProductId());
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        time_Search[i] = elapsed_seconds.count();

        comp_Search[i] = tree->getComparacaoB();

        saida << comp_Insert[i] << "\t\t\t\t\t" << time_Insert[i] << "\t\t\t\t\t\t" << comp_Search[i] << "\t\t\t\t\t" << time_Search[i] << endl;

        delete[] list;
    }

    saida << "---------------------------------------------Medias---------------------------------------------" << endl;
    saida << "Comparacoes de insercao: " << (comp_Insert[0] + comp_Insert[1] + comp_Insert[2]) / 3.0 << endl;
    saida << "Tempo de insercao: " << (time_Insert[0] + time_Insert[1] + time_Insert[2]) / 3.0 << endl;
    saida << "Comparcoes de busca: " << (comp_Search[0] + comp_Search[1] + comp_Search[2]) / 3.0 << endl;
    saida << "Tempo de insercao: " << (time_Insert[0] + time_Insert[1] + time_Insert[2]) / 3.0 << endl;




    cout << "\nEstatisticas da Arvore B" << endl;
    saida << "\n\t\t\t\t\t\tEstatisticas da Arvore B" << endl;
    for (int k = 0; k < 2; k++)
    {
        if (k == 0)
        {
            cout << "Dados para ordem(m) = 20" << endl;
            saida << "\t\t\t\t\t\tDados para ordem(m) = 20" << endl;
            saida << "Comparacoes de Insercao\t"
                  << "Tempo de insercao(s)\t\t"
                  << "Comparacoes de busca\t\t"
                  << "Tempo de busca" << endl;
        }
        else
        {
            cout << "\nDados para ordem(m) = 200" << endl;
            saida << "\n\t\t\t\t\t\tDados para ordem(m) = 200" << endl;
            saida << "Comparacoes de Insercao\t"
                  << "Tempo de insercao(s)\t\t"
                  << "Comparacoes de busca\t\t"
                  << "Tempo de busca" << endl;
        }

        for (int i = 0; i < 3; i++)
        {
            list = import(n);

            if(k == 0){
                arv = new ArvoreB(20);
            }else{
                arv = new ArvoreB(200);
            }

            std::chrono::time_point<std::chrono::system_clock> start, end;
            std::chrono::duration<double> elapsed_seconds;

            start = std::chrono::system_clock::now();
            for (int j = 0; j < n; j++)
            {
                arv->insere(&list[j]);
            }
            end = std::chrono::system_clock::now();
            elapsed_seconds = end - start;
            time_Insert[i] = elapsed_seconds.count();

            comp_Insert[i] = arv->getCompInsercao();

            start = std::chrono::system_clock::now();
            for (int j = 0; j < b; j++)
            {
                index = random_numbers() % n;
                arv->busca(list[index].getUserId(), list[index].getProductId());
            }
            end = std::chrono::system_clock::now();
            elapsed_seconds = end - start;
            time_Search[i] = elapsed_seconds.count();

            comp_Search[i] = arv->getCompBusca();

            saida << comp_Insert[i] << "\t\t\t\t\t" << time_Insert[i] << "\t\t\t\t\t\t" << comp_Search[i] << "\t\t\t\t\t" << time_Search[i] << endl;

            delete[] list;
        }

        saida << "---------------------------------------------Medias---------------------------------------------" << endl;
        saida << "Comparacoes de insercao: " << (comp_Insert[0] + comp_Insert[1] + comp_Insert[2]) / 3.0 << endl;
        saida << "Tempo de insercao: " << (time_Insert[0] + time_Insert[1] + time_Insert[2]) / 3.0 << endl;
        saida << "Comparcoes de busca: " << (comp_Search[0] + comp_Search[1] + comp_Search[2]) / 3.0 << endl;
        saida << "Tempo de insercao: " << (time_Insert[0] + time_Insert[1] + time_Insert[2]) / 3.0 << endl;
    }
}

int main(int argc, char **argv)
{
    int opcao = 1;
    int methodId;

    if (argc > 1)
    {
        path = argv[1];

        createBinary(path);
        while (opcao != 4)
        {
            cout << "Digite um valor para executar a etapa desejada: " << endl;
            cout << "[1] Estruturas Balanceadas." << endl;
            cout << "[2] Compressão." << endl;
            cout << "[3] Encerrar aplicacao." << endl;
            cin >> opcao;

            switch (opcao)
            {
                case 1:
                    gerarSaidaEstruturasBalanceadas();
                    break;
                case 2:
                    gerarSaidaCompressao();
                    break;
                case 3:
                    exit(1);
                    break;
                default:
                    cout << "Valor invalido." << endl;
                    break;
            }
        }

        return 0;
    }
    else
    {
        cout << "Problema ao informar o caminho no prompt.\n";
    }
    return 0;
}
