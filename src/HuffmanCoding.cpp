#include "HuffmanCoding.h"
#include "File.h"
#include <cstring>

#define TAM 128 //Total de caracteres da tabela ASCII

HuffmanCoding::HuffmanCoding(){
    path = "/home/ricardo/dcc-012/trabalho-dcc012/";
    
    altura = 0;

    inicializa_Lista();

    table_freq = new int[TAM];

    inicializa_com_zeros();
}

void HuffmanCoding::inicializa_Lista(){
    HuffList *list = new HuffList;
    lista = list;
    lista->inicio = NULL;
    lista->tam = 0;
}

void HuffmanCoding::insere_ordenado(NoHuff *node){

    if(lista->inicio == NULL){
        //Lista vazia
        lista->inicio = node;

    }else if(node->getFrequencia() < lista->inicio->getFrequencia()){
        //frequencia do novo cara é menor do que a frequencia do inicio da lista
        node->setProx(lista->inicio);
        lista->inicio = node;

    }else{
        NoHuff *aux = lista->inicio;
        while(aux->getProx() != NULL && aux->getProx()->getFrequencia() <= node->getFrequencia()){
            aux = aux->getProx();
        }
        node->setProx(aux->getProx());
        aux->setProx(node);

    }
    
    lista->tam++;
}

HuffmanCoding::~HuffmanCoding(){

}

void HuffmanCoding::inicializa_com_zeros(){
    for(int i = 0; i < TAM; i++)
        table_freq[i] = 0;
}

void HuffmanCoding::contabiliza_Frequencia_string(string s){
    for(int i = 0; i < s.length(); i++){
        table_freq[s[i]]++;
    }
}

void HuffmanCoding::contabilizaFrequencia(int n){

    File* arq = new File(path);

    
     
    ProductReview *vet = arq->import(n);

    
    for(int i = 0; i < n; i++){

        for(int j = 0; j < vet[i].getProductId().length(); j++){
            table_freq[vet[i].getProductId()[j]]++;
        }

        for(int j = 0; j < vet[i].getUserId().length(); j++){
            table_freq[vet[i].getUserId()[j]]++;
        }

        for(int j = 0; j < vet[i].getRating().length(); j++){
            table_freq[vet[i].getRating()[j]]++;
        }

        for(int j = 0; j < vet[i].getTimeStamp().length(); j++){
            table_freq[vet[i].getTimeStamp()[j]]++;
        }
    }
}

void HuffmanCoding::preenche_lista_prioridade(){
    for(int i = 0; i < TAM; i++){
        if(table_freq[i] > 0){
            NoHuff *node = new NoHuff();
            char c = (char) i;
            node->setCaracter(c);
            node->setFrequencia(table_freq[i]);
            node->setDir(NULL);
            node->setEsq(NULL);
            node->setProx(NULL);
            insere_ordenado(node);
        }
    }
}

void HuffmanCoding::imprime_lista_prioridade(){
    NoHuff *p = lista->inicio;

    while(p != NULL){
        cout << (char) p->getCaracter() << " + " << p->getFrequencia() << endl;
        p = p->getProx();
    }
}

NoHuff* HuffmanCoding::remove_node_inicial(){
    NoHuff* p = NULL; 

    if(lista->inicio != NULL){
        p = lista->inicio;
        lista->inicio = p->getProx();
        p->setProx(NULL); 
        lista->tam--;
    }

    return p;
}

NoHuff* HuffmanCoding::create_arvore_huffman(){
    NoHuff *first, *second;
    while(lista->tam > 1){

        first = remove_node_inicial();
        second = remove_node_inicial();

        NoHuff* novo = new NoHuff();
        novo->setEsq(first);
        novo->setDir(second);
        novo->setProx(NULL);
        novo->setCaracter('*');
        novo->setFrequencia(first->getFrequencia() + second->getFrequencia());

        insere_ordenado(novo);
    }

    return lista->inicio; //raiz da árvore de Huffman
}

void HuffmanCoding::calcula_altura_arvore(){
    altura = aux_calcula_altura_arvore(lista->inicio);
}

void HuffmanCoding::gera_Dicionario(){
    dicionario = new char*[TAM];

    for(int i = 0; i < TAM; i++){
        dicionario[i] = new char[altura+1];
    }
}

void HuffmanCoding::preenche_Dicionario(){

    gera_Dicionario();
    string c = "";
    aux_preenche_Dicionario(lista->inicio, c, altura+1);
}

void HuffmanCoding::aux_preenche_Dicionario(NoHuff *p, string caminho, int colunas){
    if(p->getEsq() == NULL && p->getDir() == NULL)
        strcpy(dicionario[p->getCaracter()], caminho.c_str());
    else{
        string esquerda, direita;

        esquerda = caminho;
        direita = caminho;

        esquerda += "0";
        direita += "1";

        aux_preenche_Dicionario(p->getEsq(), esquerda, colunas);
        aux_preenche_Dicionario(p->getDir(), direita, colunas);
    }
}

int HuffmanCoding::aux_calcula_altura_arvore(NoHuff *p){
    if(p == NULL){
        return -1;
    }else{
        int esq = aux_calcula_altura_arvore(p->getEsq());
        int dir = aux_calcula_altura_arvore(p->getDir());

        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}

void HuffmanCoding::impressao_dicionario(){
    cout << "Altura da arvore: " << altura << endl;
    for(int i = 0; i < TAM; i++){
        if(table_freq[i] > 0)
            cout << (char) i << "    " << dicionario[i] << endl;
    }
}