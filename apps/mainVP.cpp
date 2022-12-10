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

int main(){
    
    //Parte relacionada ao código de Huffman
    HuffmanCoding* teste = new HuffmanCoding();

    //Parte 1 - Contabilizar a frequência dos caracteres.
    teste->contabilizaFrequencia(2);

    //Parte 2 - Preencher uma lista de prioridade(min val) com as frequências e caracteres associados
    teste->preenche_lista_prioridade();
    teste->imprime_lista_prioridade();

    //Parte 3 - Construir a árvore de Huffman

    NoHuff* no = teste->create_arvore_huffman();
    cout << "**---------Árvore de Huffman---------**" << endl;
    imprime_arvore_huffman(no);
}

//Parte Relacionada a Árvore Vermelho e Preto
// int main(){

//     File* arq = new File("/dcc-012/trabalho-dcc012/");

//     ArvoreVP *tree = new ArvoreVP();

//     ProductReview *list = arq->import(3);

//     tree->insere(&list[0]);
//     tree->insere(&list[1]);
//     tree->insere(&list[2]);

//     tree->print();
// }
