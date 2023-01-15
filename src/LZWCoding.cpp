#include "LZWCoding.h"
#include "File.h"
#include <string>
#include <cstring>

LZWCoding::LZWCoding(ProductReview *list, int n)
{
    this->registros = n;
    this->list = list;
    LZWCompress(list);
}

LZWCoding::~LZWCoding()
{
    delete list;
}
int LZWCoding::InicializaDicionario(string dicionario[])
{
    int cont  = 0;
    for(int i = 48; i <= 57; i++)//Adicionasas numeros de 0 a 9 ao dicionario
    {
        dicionario[cont] += i;
        cont++;
    }
    for(int i = 65; i <= 90; i++)//Adiciona as letras maiusculas ao dicionario
    {
        dicionario[cont] += i;
        cont++;
    }
    //Outros caracteres que aparecem nas avaliacoes
    dicionario[cont] += ',';
    cont++;
    dicionario[cont] += '.';
    cont++;
    dicionario[cont] += '\n';
    cont++;

    return cont;
    
}

string LZWCoding::Comprime(string concatenada)//Compressor
{
    cout<<"chegou"<<endl;
    string dicionario[10000];
    string codigo = "";
    string entrada = "";
    int k;
    int posicao;
    int tamanhoD = InicializaDicionario(dicionario);
    
    for(int i = 0; i < concatenada.length(); i++)
    {
        entrada = "";
        //cout<<"I: "<<i<<endl;
        //k = 0;
        entrada = concatenada[i];
        k = i;
        for(int j = 0; j < tamanhoD; j++)
        {
            
            if(entrada == dicionario[j])//Caso encontre a correspondencia salva a posicao e adiciona o proximo caractere aa entrada
            {
                //cout<<"Comparando "<<entrada<<" com "<<dicionario[j]<<endl;
                posicao = j;
                k++;
                if(k < concatenada.length())//Verfica se já atingiu o final da string               
                {
                    entrada += concatenada[k];    
                    j = 0;//Comeca a procurar a partir do inicio do dicionario de novo
                }
            }
            //cout<<"J:"<<j<<endl;            
        }
        i = k-1;
        //cout<<"Entrada: "<<entrada<<endl;
        if(k < concatenada.length())
        {
            dicionario[tamanhoD] = entrada;
            tamanhoD++;
        }
        //cout<<"Dicionario: "<<dicionario[tamanhoD]<<endl;
        //cout<<"Posicao: "<<posicao<<endl;
        codigo += posicao;
        /*int aux = posicao;
        cout<<"Codigo: "<<aux<<endl<<endl;*/
    }
    cout<<"Codigo: "<<codigo<<endl;
    /*cout<<"Inteiros: ";
    for(int h = 0; h < codigo.length(); h++)
    {
        int p = codigo[h];
        cout<< p <<" ";
    }
    for(int h = 0; h < tamanhoD; h++)
    {
        cout<< "string "<<h<<": "<<dicionario[h] <<endl;
    }
    */
    cout<<concatenada.length()<<" -> ";
    cout<<codigo.length();
    return codigo;
}

string LZWCoding::Descomprime(string codigo)
{
    string descomp = "";
    
    return descomp;
}

void LZWCoding::LZWCompress(ProductReview *list) // Algoritmo LZW de compressao
{

    string concatenada = "";
    string dicionario[1000]="";
    
    for(int i = 0; i < registros; i++)//Concatena a lista em uma única string
    {
        concatenada += list[i].getUserId() +',' + list[i].getProductId() +',' + list[i].getRating() +',' + list[i].getTimeStamp()+'\n';
    }
    cout<<"Concatenada: "<<endl<<concatenada<<endl;
    //InicializaDicionario(dicionario);
    Comprime(concatenada);
    
    
    
}