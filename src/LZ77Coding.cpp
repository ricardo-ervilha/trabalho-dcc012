#include "LZ77Coding.h"
#include "File.h"
#include <string>
#include <cstring>

#define ND 6 // Tamanho do Dicionário
#define NB 4 // Tamanho do Buffer
/*
    1: Defina os tamanhos Nd e Nb do dicionário e do buffer
    2: Inicialize o buffer com os primeiros Nb caracteres da sequência
        Obs: Pode inicializar o dicionário com o primeiro caractere do buffer ou deixar ele vazio
    3: Enquanto houver símbolos a codificar
        3.1: Identifique a maior sequência do buffer que pode ser encontrada a partir de uma posição do dicionário
        3.2: Emita o código correspondente a esta sequência
        3.3: Avance a janela por l+1 posições, sendo l o tamanho da sequência encontrada
    4: Utiliza-se uma tripla (p, l, c) para codificar a sequência
        p: posição no dicionário a partir do cursor
        l: comprimento da sequência
        c: primeiro caractere após a sequência (aquele que encerra a sequência)
        A janela é deslocada l+1 posições para a direita
        Quando não há correspondência no dicionário, o código (0, 0, c) é emitido,
        sendo c o caractere sob o cursor





codigo += ('0'+ p);
                codigo += ('0'+ l);
                c = concatenada[cursorB];
                cout << "p l c " << p << l << c << endl;
                cursorB++;
                codigo += c;
                codigo += " ";
                inicialPosD++;
                    cursorD++;
                    finalPosD++;
                    cursorB++;
                    finalPosB++;
*/
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



void LZ77Coding::LZ77Compress(ProductReview *list) // Algoritmo LZ77 de compressao
{

    string concatenada = "";
    string codigo = "";                               // String para armazenar o codigo pos-compressao
    int cursorD = 0, inicialPosD = 0, finalPosD = -1; // cursor ,posição inicial e final do dicionário em relação a string concatenada
    int cursorB = 0, finalPosB = 0;                   // cursor e posição final do Buffer em relação a string concatenada

    /*for(int i = 0; i < registros; i++)//Concatena a lista em uma única string
    {
        concatenada += list[i].getUserId() +',' + list[i].getProductId() +',' + list[i].getRating() +',' + list[i].getTimeStamp()+'\n';
    }*/
    // cout<<concatenada;
    concatenada = "bananabanabofana";
    for (int i = 0; i < NB; i++) // Ajusta a posição final do buffer
    {
        finalPosB++;
    }
    finalPosB--;

    // Variaves para criacao do codigo comprimido
    int p = 0; // Posicoes antes do cursor
    int l = 0; // quantidade de caracteres na sequencia
    char c;    // caractere apos a sequencia
    for (int i = 0; (i < concatenada.length()) && (cursorB <= concatenada.length()); i++)
    {

        cursorD = inicialPosD;
        cout << endl << endl << "Dicionario: ";
        for (int h = inicialPosD; h <= finalPosD; h++)
        {
            cout << concatenada[h];
        }
        cout<<endl<<"Cursor Dicionario em: " << concatenada[cursorD] << endl;
        cout << "Buffer: ";
        for (int h = cursorB; h <= finalPosB; h++)
        {
            cout << concatenada[h];
        }
        cout<<endl<<"Cursor Buffer em: "<< concatenada[cursorB] << endl;
        cout<<"Codigo:" << codigo << endl;
        cout<<"Tamanho dicionario: "<<finalPosD - inicialPosD<<endl;
        cout<<"Tamanho buffer: "<<finalPosB - cursorB<<endl;



        
        l = 0;
        if (finalPosD == -1)//Primeiro Caso
        {
            // Gera o primeiro codigo
            codigo += '0';
            codigo += '0';
            codigo += concatenada[cursorB];
            codigo += " ";
            // Ajusta as posicoes do dicionario e buffer
            cursorB++;
            finalPosB++;
            finalPosD++;
        }
        else//Segundo caso em diante 
        { 
            // Percorre a parte da string que esta sendo utilizada como dicionario dicionario
            p = 0;
            l = 0;
            if (concatenada[cursorD] == concatenada[cursorB])
            {
                p = cursorB - cursorD;
                while ((concatenada[cursorD] == concatenada[cursorB]) && (cursorD < finalPosD))
                {

                    // Ajusta as posições inicias, finais, dos cursores e quantidade de caracacteres em sequencia
                    cursorB++;
                    cursorD++;
                    finalPosB++;
                    finalPosD++;
                    l++;
                    // Caso o dicionario fique maior que o tamanho definido sua posicao inical muda
                    while ((finalPosD - inicialPosD) > ND)
                    {
                        inicialPosD++;
                    }
                }
                

                c = concatenada[cursorB];
                codigo += ('0' + p);
                codigo += ('0' + l);
                codigo += c;
                codigo += ' ';
                
                
                
            }
            else
            {
                // Procura no Dicionario uma ocorrencia do padrao
                while ((concatenada[cursorD] != concatenada[cursorB]) && (cursorD < finalPosD))
                {
                    cursorD++;
                }
                //cout<<"Cursor parou em: "<<concatenada[cursorD]<<endl;
                //cout<<endl;
                if (concatenada[cursorD] == concatenada[cursorB])
                {
                    p = cursorB - cursorD;
                    while ((concatenada[cursorD] == concatenada[cursorB]) && (cursorD <= finalPosD))
                    {

                        // Ajusta as posições inicias, finais, dos cursores e quantidade de caracacteres em sequencia
                        cursorB++;
                        cursorD++;
                        finalPosB++;
                        finalPosD++;
                        l++;
                        // Caso o dicionario fique maior que o tamanho definido sua posicao inical muda
                        //cout<<"Tamanho dic: "<<finalPosD - inicialPosD<< endl;
                        while ((finalPosD - inicialPosD) > ND)
                        {
                            inicialPosD++;
                        }
                    }
                    if(cursorB > concatenada.length()-1)
                        c = 0;
                    else
                    c = concatenada[cursorB];
                    codigo += ('0' + p);
                    codigo += ('0' + l);
                    codigo += c;
                    codigo += ' ';
                    cursorB++;
                    finalPosB++;
                    finalPosD++;
                    while ((finalPosD - inicialPosD) > ND)
                    {
                        inicialPosD++;
                    }
                }
                else
                {
                    codigo += '0';
                    codigo += '0';
                    codigo += concatenada[cursorB];
                    codigo += ' ';
                    cursorB++;
                    finalPosB++;
                    finalPosD++;
                    while ((finalPosD - inicialPosD) > ND)
                    {
                        inicialPosD++;
                    }
                }
                
            }
            
            
            
            
        }
        /*cout << endl
             << "Letra cursor D: " << concatenada[cursorD] << endl
             << "Letra cursor B: " << concatenada[cursorB] << endl;
        cout << "Posicao inicial Dic: " << inicialPosD << endl;
        cout << "Posicao cursor Dic: " << cursorD << endl;
        cout << "Posicao final Dic: " << finalPosD << endl;
        cout << "Posicao final Buffer: " << finalPosB << endl;
        cout << "Posicao cursor Buffer: " << cursorB << endl;
        cout << "P:" << p << endl;
        cout << "L:" << l << endl;
        cout << codigo << endl;
        cout << endl
             << codigo;*/
        
        
    }
    cout<<codigo;
}