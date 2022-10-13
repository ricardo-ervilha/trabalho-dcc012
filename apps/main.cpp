#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "ProductReview.h"
#include "ListaEncad.h"

using namespace std;

void escreveArquivoBinario()
{   
    ifstream arqCsv("ratings_Electronics.csv");
    fstream arq("ratings.bin", ios::out | ios::binary);

    if(arqCsv.is_open()){
    if(arq.is_open())
    {
       string linha;
       string linhaAux;
       while(getline(arqCsv,linha)){
       stringstream aux(linha); //cria um objeto de stringstream o qual referencia a string linha
        while(getline(aux, linhaAux, ',')){ //realiza a separação dos dados do arquivo utilizando a vírgula como separador
                arq.write(reinterpret_cast<const char*>(linhaAux.c_str()), linha.length());
        }
       }
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

int main(){

    ProductReview* a = new ProductReview("ABX8" , "YTU7" , 3, 105896); 
    ProductReview* b = new ProductReview("IBX9" , "KRT3" , 4, 114567); 
    ProductReview* c = new ProductReview("U55K" , "OUZ7" , 2, 105896); 
    ProductReview* d = new ProductReview("PO34" , "FPQ0" , 0, 105896); 
    ProductReview* e = new ProductReview("ABLO" , "056J" , 1, 105896); 
    
    
    ListaEncad* lista = new ListaEncad();

    lista->insereInicio(a);
    lista->insereFinal(b);
    lista->insereFinal(c);
    lista->insereFinal(d);
    lista->insereFinal(e);

    lista->printList();

/*     cout << "Resultado da busca: " << std::boolalpha << lista->busca("YTU7") << endl;

    cout << "Elemento indice [0]: ";  lista->get(0)->print();
    cout << "Elemento indice [2]: ";  lista->get(2)->print();
    cout << "Elemento indice [4]: ";  lista->get(4)->print();  

    ProductReview* f = new ProductReview("H99N", "GZZ6", 4, 1023450);
    cout << "Mudanca no k = 3 da lista." << endl;
    lista->set(3, f);

    lista->printList(); */
/* 
    ProductReview* g = new ProductReview("KKK3" , "AA21", 3, 9821340);
    cout << "Inserindo um novo No no comeco: " << endl;
    lista->insere(g, 0);

    ProductReview* h = new ProductReview("PUKO" , "A721", 3, 9821340);
    cout << "Inserindo um novo No no final: " << endl;
    lista->insere(h, 6); */

    //lista->printList();

    /*ProductReview* i = new ProductReview("ABCD" , "UNNB", 3, 2721340);
    cout << "Inserindo um novo No na posicao k=3: " << endl;
    lista->insere(i, 3);*/

    lista->removeInicio(); //sai o a
    lista->removeFinal(); //sai o e
    lista->remove(1); //sai o b

    lista->printList();

    escreveArquivoBinario();

    return 0;
}