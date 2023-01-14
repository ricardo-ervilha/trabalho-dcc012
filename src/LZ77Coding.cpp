#include "LZ77Coding.h"
#include "File.h"
#include <string>
#include <cstring>

#define ND 80// Tamanho do Dicionário
#define NB 20 // Tamanho do Buffer
LZ77Coding::LZ77Coding(ProductReview *list, int n)
{
    this->registros = n;
    this->list = list;
    LZ77Compress(list);
}

LZ77Coding::~LZ77Coding()
{
    delete list;
}

void LZ77Coding::Comprime(string concatenada)
{
    string codigo = "";                               // String para armazenar o codigo pos-compressao
    int cursorD = 0, inicialPosD = 0,auxCursorD = 0, finalPosD = -1; // cursor ,posição inicial e final do dicionário em relação a string concatenada
    int cursorB = 0,auxCursorB = 0 , finalPosB = 0;                   // cursor e posição final do Buffer em relação a string concatenada

    for (int i = 0; i < NB; i++) // Ajusta a posição final do buffer
    {
        finalPosB++;
    }
    finalPosB--;
    
    // Variaves para criacao do codigo comprimido
    int p = 0, auxP = 0; // Posicoes antes do cursor
    int l = 0, auxL = 0; // quantidade de caracteres na sequencia
    char c;    // caractere apos a sequencia

    //cout<<concatenada<<endl;
    
    for (int i = 0; (i < concatenada.length()) && (cursorB <= concatenada.length()); i++)
    {

        cursorD = inicialPosD;
        char zero = 0;
        if (finalPosD == -1)//Primeiro Caso
        {
            // Gera o primeiro codigo
            codigo += zero;
            codigo += zero;
            codigo += concatenada[cursorB];
            // Ajusta as posicoes do dicionario e buffer
            cursorB++;
            finalPosB++;
            finalPosD++;
        }
        else//Segundo caso em diante 
        { 
            auxP = 0;
            auxL = 0; 
            p = 0;
            l = 0;
            if (concatenada[cursorD] == concatenada[cursorB])
            {
                p = cursorB - cursorD;

                for(int k = inicialPosD; k <= finalPosD; k++)//Verifica a maior ocorrencia do padrao
                {
                    //Auxiliares para verificar a maior ocorrencia do padrao
                    auxCursorB = cursorB;
                    auxCursorD = k;
                    auxL = 0;
                    while(concatenada[auxCursorD] == concatenada[auxCursorB])
                    {
                        auxCursorD++;
                        auxCursorB++;
                        auxL++;
                    }
                    if(auxL > l)
                    {
                        l = auxL;
                        p = cursorB - k;
                    }
                }
                cursorB += l;
                c = concatenada[cursorB];
                codigo += (0 + p);
                codigo += (0 + l);
                codigo += c;
                finalPosB += l + 1;
                cursorB ++;
                finalPosD += l + 1;              
                while ((finalPosD - inicialPosD) > ND)
                {
                    inicialPosD++;
                }
            }
            else
            {
                while ((concatenada[cursorD] != concatenada[cursorB]) && (cursorD < finalPosD))
                {
                    cursorD++;
                }
                if (concatenada[cursorD] == concatenada[cursorB])
                {
                    p = cursorB - cursorD;
                    for(int k = inicialPosD; k <= finalPosD; k++)//Verifica a maior ocorrencia do padrao
                    {
                        //Auxiliares para verificar a maior ocorrencia do padrao
                        auxCursorB = cursorB;
                        auxCursorD = k;
                        auxL = 0;
                        while(concatenada[auxCursorD] == concatenada[auxCursorB])
                        {
                            auxCursorD++;
                            auxCursorB++;
                            auxL++;
                        }
                        if(auxL > l)
                        {
                            l = auxL;
                            p = cursorB - k;
                        }
                    }
                    cursorB += l;
                    if(cursorB >= concatenada.length())//CAso o cursor do buffer esteja no final da string
                        c = '\0';
                    else
                        c = concatenada[cursorB];
                    codigo += (0 + p);
                    codigo += (0 + l);
                    codigo += c;
                    while ((finalPosD - inicialPosD) > ND)
                    {
                        inicialPosD++;
                    }
                    finalPosB += l + 1;
                    cursorB ++;
                    finalPosD += l + 1; 
                    while ((finalPosD - inicialPosD) > ND)
                    {
                        inicialPosD++;
                    }          
                    
                }
                else
                {
                    codigo += zero;
                    codigo += zero;
                    codigo += concatenada[cursorB];
                    cursorB++;
                    finalPosB++;
                    finalPosD++;
                    while ((finalPosD - inicialPosD) > ND)
                    {
                        inicialPosD++;
                    }
                    //codigo+=' ';
                }   
            }
        } 
    }
    cout<<"\nCodigo \n"<<codigo<<endl;
    Descomprime(codigo);
}
void LZ77Coding::Descomprime(string codigo)
{
    string palavra = "";
    int p,l,tam;
    for(int i = 0; i <= codigo.length()-2; i+=3)
    {
        if(codigo[i]==0 && codigo[i+1]==0)
        {
            palavra+= codigo[i+2];
        }
        else
        {
            p = codigo[i] - 0;
            l = codigo[i+1] - 0;
            tam =  palavra.length();
            
            for(int j = (tam - p); j < (tam - p) + l; j++)
            {
                palavra += palavra[j];
            }
            
            palavra += codigo[i+2];
        }
    }
    cout<<"\nDecodificado\n"<<palavra<<endl;
    cout<<"Tamanho palavra:"<<palavra.length()<<endl;
    cout<<"A string passou de "<<palavra.length()<<" caracteres para -> "<<codigo.length()<<" caracteres"<<endl;

}
void LZ77Coding::LZ77Compress(ProductReview *list) // Algoritmo LZ77 de compressao
{

    string concatenada = "";
    
    for(int i = 0; i < registros; i++)//Concatena a lista em uma única string
    {
        concatenada += list[i].getUserId() +',' + list[i].getProductId() +',' + list[i].getRating() +',' + list[i].getTimeStamp()+'\n';
    }
    cout<<"Concatenada: "<<endl<<concatenada<<endl;
    Comprime(concatenada);
    
    
    
}