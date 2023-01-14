#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <time.h>
#include "ProductReview.h"
#include "File.h"
#include <chrono>
#include "HashProduct.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "BucketSort.h"
#include <fstream>
#include "ArvoreVP.h"
#include "HuffmanCoding.h"

void imprime_arvore_huffman(NoHuff *p){
    
    if(p->getEsq() == NULL && p->getDir() == NULL){
        cout << p->getCaracter() << " + " << p->getFrequencia() << endl;
    }else{
        imprime_arvore_huffman(p->getEsq());
        imprime_arvore_huffman(p->getDir());
    }
}

// void comprime(int metodo){
    
//     string txt = "";
//     int a = 100000;

//     if(metodo == 0)
//     {
//         ifstream arqTxt(pathTxt);

//         char *buffer = new char[a];

//         if(arqTxt.is_open()){
//             while(!eof(arqTxt)){
//                 arqTxt.read(buffer, a);
//                 txt += buffer;
//             }
//             delete [] buffer;
//         }

//         else 
//             cerr << "Erro ao tentar abrir o arquivo .txt" << endl;


//         HuffmanCoding* teste = new HuffmanCoding;
//         teste->contabiliza_Frequencia_string(txt);
//         teste->preenche_lista_prioridade();
        
//         NoHuff* no = teste->create_arvore_huffman();
//         teste->preenche_Dicionario();

//         string comp = teste->comprime(txt);

//         fstream arqBin(pathBin);

//         if(arqBin.is_open()){
//             arqBin.write(reinterpret_cast<const char *>(comp.c_str()), comp.length());
//         }

//         else
//             cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
//     }
// }

// void decomprime(int metodo)
// {
//     string txt = "";
//     int a = 100000;

//     if(metodo == 0)
//     {
//         ifstream arqBin(pathBin);

//         char *buffer = new char[a];

//         if(arqBin.is_open()){
//             while(!eof(arqBin)){
//                 arqBin.read(buffer, a);
//                 txt += buffer;
//             }
//             delete [] buffer;
//         }

//         else 
//             cerr << "Erro ao tentar abrir o arquivo .txt" << endl;


//         HuffmanCoding* teste = new HuffmanCoding;
//         teste->contabiliza_Frequencia_string(txt);
//         teste->preenche_lista_prioridade();
        
//         NoHuff* no = teste->create_arvore_huffman();
//         teste->preenche_Dicionario();

//         string descomp = teste->descomprime(txt);

//         fstream arqTxt(pathTxt);

//         if(arqTxt.is_open()){
//             arqTxt << descomp;
//         }

//         else
//             cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
//     }
// }

// int main(){
    
//     //Parte relacionada ao código de Huffman
//     HuffmanCoding* teste = new HuffmanCoding();

//     //Parte 1 - Contabilizar a frequência dos caracteres.
//     //teste->contabilizaFrequencia(2);
//     cout << "Teste 1\n";
//     teste->contabiliza_Frequencia_string("eeisieeiiieaaiiie");
//     cout << "Teste 2\n";
//     //Parte 2 - Preencher uma lista de prioridade(min val) com as frequências e caracteres associados
//     teste->preenche_lista_prioridade();
//     teste->imprime_lista_prioridade();

//     //Parte 3 - Construir a árvore de Huffman
//     NoHuff* no = teste->create_arvore_huffman();
//     cout << "**---------Árvore de Huffman---------**" << endl;
//     imprime_arvore_huffman(no);

//     //Parte 4 - Construção do Dicionário
    
//     teste->calcula_altura_arvore();
    
//     teste->preenche_Dicionario();
//     cout << "*---------Dicionário de Compressão---------**" << endl;
    
//     teste->impressao_dicionario();

//     cout << teste->comprime("eeisieeiiieaaiiie") << endl;
//     cout << teste->descomprime("11110100011110001110110100011") << endl;
// }





//Parte Relacionada a Árvore Vermelho e Preto
int main(){

    File* arq = new File("/home/pedro/EDII/trabalho-dcc012/");
    int n;

    cout << "Digite a quantidade de registros a serem importados: ";
    cin >> n;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
 
    ProductReview *list;
    ArvoreVP *tree;

    for(int i = 0; i < 3; i++){
        list = arq->import(n); 
        tree = new ArvoreVP(arq);
        for(int j = 0; j < n; j++)
        {
            tree->insere(&list[j]);
        }
        cout << tree->getComparacaoIn() << endl;
        delete []list;    
    }

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    cout << "Tempo de insercao na arvore: " << elapsed_seconds.count() << endl;

    int comp = 0, B;

    cout << "Digite o numero de registros para serem buscados na arvore escolhida: ";
    cin >> B;

    start = std::chrono::system_clock::now();

    ProductReview* list2 = arq->import(100);

    for(int i = 0; i < B; i++){
        ProductReview* pr = tree->busca((&list[i])->getUserId(), (&list[i])->getProductId());
        comp = tree->getComparacaoB();
        cout << comp << endl;

    }

    delete []list;

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds2 = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    cout << "Tempo de busca de " << B << " ProductReviews na arvore escolhida: " << elapsed_seconds2.count() << endl;

    return 0;
}
