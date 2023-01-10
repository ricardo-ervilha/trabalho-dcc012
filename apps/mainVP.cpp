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

void comprime(int metodo){
    
    string txt = "";
    int a = 100000 

    if(metodo == 0)
    {
        ifstream arqTxt(pathTxt);

        char *buffer = new char[a];

        if(arqTxt.is_open()){
            while(!eof(arqTxt)){
                arqTxt.read(buffer, a);
                txt += buffer;
            }
            delete [] buffer;
        }

        else 
            cerr << "Erro ao tentar abrir o arquivo .txt" << endl;


        HuffmanCoding* teste = new HuffmanCoding;
        teste->contabiliza_Frequencia_string(txt);
        teste->preenche_lista_prioridade();
        
        NoHuff* no = teste->create_arvore_huffman();
        teste->preenche_Dicionario();

        string comp = teste->comprime(txt);

        fstream arqBin(pathBin);

        if(arqBin.is_open()){
            arqBin.write(reinterpret_cast<const char *>(comp.c_str()), comp.length());
        }

        else
            cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
    }
}

void decomprime(int metodo)
{
    string txt = "";
    int a = 100000

    if(metodo == 0)
    {
        ifstream arqBin(pathBin);

        char *buffer = new char[a];

        if(arqBin.is_open()){
            while(!eof(arqBin)){
                arqBin.read(buffer, a);
                txt += buffer;
            }
            delete [] buffer;
        }

        else 
            cerr << "Erro ao tentar abrir o arquivo .txt" << endl;


        HuffmanCoding* teste = new HuffmanCoding;
        teste->contabiliza_Frequencia_string(txt);
        teste->preenche_lista_prioridade();
        
        NoHuff* no = teste->create_arvore_huffman();
        teste->preenche_Dicionario();

        string descomp = teste->descomprime(txt);

        fstream arqTxt(pathTxt);

        if(arqTxt.is_open()){
            arqTxt << descomp;
        }

        else
            cerr << "Erro ao tentar abrir o arquivo .bin" << endl;
    }
}

int main(){
    
    //Parte relacionada ao código de Huffman
    HuffmanCoding* teste = new HuffmanCoding();

    //Parte 1 - Contabilizar a frequência dos caracteres.
    //teste->contabilizaFrequencia(2);
    cout << "Teste 1\n";
    teste->contabiliza_Frequencia_string("eeisieeiiieaaiiie");
    cout << "Teste 2\n";
    //Parte 2 - Preencher uma lista de prioridade(min val) com as frequências e caracteres associados
    teste->preenche_lista_prioridade();
    teste->imprime_lista_prioridade();

    //Parte 3 - Construir a árvore de Huffman
    NoHuff* no = teste->create_arvore_huffman();
    cout << "**---------Árvore de Huffman---------**" << endl;
    imprime_arvore_huffman(no);

    //Parte 4 - Construção do Dicionário
    
    teste->calcula_altura_arvore();
    
    teste->preenche_Dicionario();
    cout << "*---------Dicionário de Compressão---------**" << endl;
    
    teste->impressao_dicionario();

    cout << teste->comprime("eeisieeiiieaaiiie") << endl;
    cout << teste->descomprime("11110100011110001110110100011") << endl;
}





//Parte Relacionada a Árvore Vermelho e Preto
// int main(){

//     File* arq = new File("/home/pedro/EDII/trabalho-dcc012/");

//     ArvoreVP *tree = new ArvoreVP(arq);

//     ProductReview *list = arq->import(4);

//     tree->insere(&list[0]);
//     tree->insere(&list[1]);
//     tree->insere(&list[2]);

//     cout << "UserId: " << (&list[1])->getUserId() << endl;
//     cout << "ProductId: " << (&list[1])->getProductId() << endl;

//     tree->print();

//     ProductReview* pr = tree->busca((&list[1])->getUserId(),(&list[1])->getProductId());

//     if(pr != NULL){
//     cout << "UserId pr: " << pr->getUserId() << endl;
//     cout << "ProductId pr: " << pr->getProductId() << endl;
//     }

// }
