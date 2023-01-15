#include "LZWCoding.h"
#include "File.h"
#include <string>
#include <cstring>

LZWCoding::LZWCoding()
{

}

LZWCoding::~LZWCoding()
{
    
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
    string dicionario[10000];
    string codigo = "";
    string entrada = "";
    int k;
    int posicao;
    int tamanhoD = InicializaDicionario(dicionario);
    
    for(int i = 0; i < concatenada.length(); i++)
    {
        entrada = "";
        entrada = concatenada[i];
        k = i;
        for(int j = 0; j < tamanhoD; j++)
        {
            
            if(entrada == dicionario[j])//Caso encontre a correspondencia salva a posicao e adiciona o proximo caractere aa entrada
            {
                posicao = j;
                k++;
                if(k < concatenada.length())//Verfica se já atingiu o final da string               
                {
                    entrada += concatenada[k];    
                    j = 0;//Comeca a procurar a partir do inicio do dicionario de novo
                }
            }
           
        }
        i = k-1;
        if(k < concatenada.length())
        {
            dicionario[tamanhoD] = entrada;
            tamanhoD++;
        }
        codigo +=posicao;
    }
    Descomprime(codigo);
    return codigo;
}

string LZWCoding::Descomprime(string codigo)
{
    string descomp = "";
    string dicionario[10000];
    int tamD;//Tamanho do dicionario
    tamD = InicializaDicionario(dicionario);
    descomp += dicionario[codigo[0]];
    for(int i = 1; i < codigo.length(); i++)
    {
        descomp += dicionario[codigo[i]];
        dicionario[tamD] = dicionario[codigo[i-1]] + dicionario[codigo[i]][0];//Adiciona ao dicionario o primeiro caractere do codigo atual 
                                                                              //e a string do codigo anterior
        tamD++;              
    }
    return descomp;
}
