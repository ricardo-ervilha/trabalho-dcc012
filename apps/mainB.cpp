#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "ArvoreB.h"
#include "ProductReview.h"
#include "ArvoreB.h"
#include "ArvoreVP.h"
#include "File.h"
#include <cstring>
#include <time.h>
#include <chrono>
#include "Hash.h"
#include "HuffmanCoding.h"
#include "LZ77Coding.h"
#include <fstream>

using namespace std;
using namespace std::chrono;

#define maxU 21
#define maxT 10
#define MAXCSV 7824482

string path;
NoHuff *raiz;

string completeString(int n, string s)
{
    for (int i = 0; i < n; i++)
    {
        s += '?';
    }
    return s;
}

char *zeraVetor(int n, char *vet)
{

    for (int i = 0; i < n; i++)
        vet[i] = '!';
    return vet;
}

void createBinary(string &path_linha)
{
    path = path_linha;
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

        // caracteres que devem ser usados para split.
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

void getReview(int i)
{
    ifstream arq(path + "ratings.bin", ios::binary);
    cout << "PATH: " << path + "ratings.bin" << endl;
    if (arq.is_open())
    {
        char userId[22], productId[11], ratings[4], timeStamp[11];
        arq.seekg(i * 44); // Cada registro contém 44 bytes por padrão.

        arq.read(userId, 21);

        for (int i = 0; i < 21; i++)
        {
            if (userId[i] == '?')
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
        for (int i = 0; i < 11; i++)
        {
            if (timeStamp[i] == '?')
            {
                timeStamp[i] = '\0';
                break;
            }
        }
        timeStamp[10] = '\0';
        cout << timeStamp << endl;
    }
    else
    {
        cout << "ERRO!: arquivo não está aberto!" << endl;
    }

    arq.close();
}

ProductReview converteReview(int i)
{
    string filePath = path + "ratings.bin";
    ifstream arq(filePath, ios::binary);

    char userId[22], productId[11], ratings[4], timeStamp[11];

    if (arq.is_open())
    {
        arq.seekg(i * 44);
        arq.read(userId, 21);

        for (int i = 0; i < 21; i++)
        {
            if (userId[i] == '?')
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
    }
    else
    {
        cout << "ERRO: Falha ao abrir o arquivo(converteReview).\n";
        cout << "Caminho: " << filePath << endl;
        exit(1);
    }

    arq.close();

    // converter os chars de volta para string
    string usID(userId);
    string prodId(productId);
    string rat(ratings);
    string timeSt(timeStamp);

    // gera o registro
    ProductReview review(usID, prodId, ratings, timeStamp, i);

    return review;
}

// Função para gerar os indices aleatorios que serão pulados no arquivo binario pela seekg.
unsigned long long random_numbers()
{
    unsigned long long r = 0;

    for (int i = 0; i < 5; ++i)
    {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    return r & 0xFFFFFFFFFFFFFFFFULL;
}

ProductReview *import(int n)
{

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

// Método auxiliar para calcular o tamanho da string antes e pós-compressão.
int computaTamanhoString(string txt, bool flag)
{
    if (flag)
    {
        return txt.length() * 8; // True -> string antes de comprimir
    }
    else
    {
        return txt.length(); // False -> string depois de comprimir
    }
}

// Método auxiliar para concatenação da string dos registros
string concatenaRegistros(ProductReview *registros, int n)
{

    string texto = "";

    for (int i = 0; i < n; i++)
    {
        texto += (registros[i].getProductId() + registros[i].getUserId() + registros[i].getTimeStamp() + registros[i].getRating());
    }

    return texto;
}

// Comprime uma string qualquer passsada como parâmetro.
string comprime(string str, int metodo)
{

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
        // Compressão do LZ77
        return "string";
    }
    else
    {
        // Compressão do LZW
        return "string";
    }
}

string auxDescomprime(NoHuff *p, string str, string descomp, int i)
{
    if (p->getEsq() == NULL && p->getDir() == NULL)
    { // eh folha

        descomp += p->getCaracter();

        if (i < str.length())
            return auxDescomprime(raiz, str, descomp, i);

        else
            return descomp;
    }

    if (str[i] == '0')
        return auxDescomprime(p->getEsq(), str, descomp, i + 1);
    else
        return auxDescomprime(p->getDir(), str, descomp, i + 1);
}

// Descomprime uma string qualquer passsada como parâmetro.
string descomprime(string str, int metodo)
{

    if (metodo == 0)
    {
        // Descompressão do Huffman
        string descomp = "";

        return auxDescomprime(raiz, str, descomp, 0);
    }
    else if (metodo == 1)
    {
        // Descompressão do LZ77
        return "string";
    }
    else
    {
        // Descompressão do LZW
        return "string";
    }
}

// Comprime um arquivo.
void comprime(int metodo)
{

    if (metodo == 0)
    {
        // Huffman
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
        HuffmanCoding *huff = new HuffmanCoding;
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
        // LZ77
    }
    else
    {
        // LZW
    }
}

// Descomprime um arquivo.
void descomprime(int metodo)
{
    string txt = "";
    string dic = "";
    string pathBin = path + "reviewsComp.bin";
    string pathTxt = path + "reviewsDesc.txt";
    bool aux = true;

    int a = 100000;

    if (metodo == 0)
    {
        ifstream arqBin(pathBin);

        string line;

        if (arqBin.is_open())
        {
            while (getline(arqBin, line))
            {
                if (aux)
                {
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
        HuffmanCoding *huff = new HuffmanCoding;

        huff->adicionaNovaLista(dic);
        huff->preenche_lista_prioridade();
        // teste->imprime_lista_prioridade();

        NoHuff *no = huff->create_arvore_huffman();
        huff->preenche_Dicionario();

        string descomp = huff->descomprime(txt);

        fstream arqTxt(pathTxt);

        if (arqTxt.is_open())
        {
            arqTxt << descomp;
        }
        else
            cerr << "Erro ao tentar abrir o arquivo .txt" << endl;

        arqTxt.close();
    }
    else if (metodo == 1)
    {
        // LZ77
    }
    else
    {
        // LZW
    }
}

//------------------------ TestesP2 - Caniato ------------------------
void printPrompt(ProductReview *vet, int n)
{
    char imp;
    cout << "Imprimir (s/n): ";
    cin >> imp;

    if (vet == NULL)
        cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
    else if (imp == 's')
    {
        for (int i = 0; i < n; i++)
            vet[i].print();
    }
}

void printPrompt(ArvoreVP *arv, int n)
{
    char imp;
    cout << "Imprimir (s/n): ";
    cin >> imp;

    if (arv == NULL)
        cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
    else if (imp == 's')
        arv->print();
}

void printPrompt(ArvoreB *arv, int n)
{
    char imp;
    cout << "Imprimir (s/n): ";
    cin >> imp;

    if (arv == NULL)
        cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
    else if (imp == 's')
        arv->print();
}

ProductReview *randomTest(int n)
{
    ProductReview *vet = new ProductReview[n];

    for (int i = 0; i < n; i++)
    {
        string u("STR");
        u += 'a' + rand() % ('z' - 'a');
        // vet[i].userId = u; // ou essa linha ou a de baixo pode ser usada, dependendo de como foi implementado (a de baixo é preferencial)
        vet[i].setUserId(u);
    }

    return vet;
}

template <typename T>
void treeTest(T arv, ProductReview *vet, int n)
{
    for (int i = 0; i < n; i++)
        arv->insere(&vet[i]);
    printPrompt(vet, n);

    string userId, productId;
    cout << "Digite um par (userId, productId) para busca: ";
    cin >> userId >> productId;
    while (userId != "quit")
    {
        ProductReview *p = arv->busca(userId, productId);
        if (p != NULL)
            p->print();
        else
            cout << "Produto nao encontrado!" << endl;

        cout << "Digite outro par (userId, productId) para busca: ";
        cin >> userId >> productId;
    }
}

void compressTest(int method)
{
    switch (method)
    {
    case 0:
        cout << "=== Teste Huffman ===" << endl
             << endl;
        break;
    case 1:
        cout << "=== Teste LZ77 ===" << endl
             << endl;
        break;
    case 2:
        cout << "=== Teste LZW ===" << endl
             << endl;
        break;
    default:
        cout << "Metodo de compressao nao suportado" << endl
             << endl;
        break;
    }

    cout << "Testando strings..." << endl;

    string str = "string qualquer";
    string comp = comprime(str, method);
    string orig = descomprime(comp, method);

    cout << "String comprimida: " << comp << endl;
    cout << "String descomprimida: " << orig << endl
         << endl;

    cout << "Testando arquivos..." << endl;

    comprime(method);    // essa função deve comprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsOrig.txt'
    descomprime(method); // essa função deve descomprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsComp.bin'
}

// int main(int argc, char *argv[])
// {
//     if(argc > 1)
//     {
//         // OBS.: TODOS OS ARQUIVOS USADOS NO PROGRAMA (TANTO DE ENTRADA QUANTO DE SAÍDA) DEVEM ESTAR LOCALIZADOS NO DIRETÓRIO FORNECIDO
//         // PELO USUÁRIO COMO ARGUMENTO DA LINHA DE COMANDO
//         std::string path(argv[1]);
//         createBinary(path);

//         int registerIdx;
//         cout << "Digite um indice de registro (-1 para sair): ";
//         cin >> registerIdx;
//         while (registerIdx != -1)
//         {
//             getReview(registerIdx);
//             cout << "Digite outro indice de registro (-1 para sair): ";
//             cin >> registerIdx;
//         }

//         ProductReview *vet = 0;
//         ArvoreVP *arv_vp = 0;
//         ArvoreB *arv_b = 0;
//         int option, n;
//         do
//         {
//             cout << "[1] Vetor de teste" << endl
//                 << "[2] Importar registros" << endl
//                 << "[3] Arvore vermelho-preto" << endl
//                 << "[4] Arvore B" << endl
//                 << "[5] Huffman" << endl
//                 << "[6] LZ77" << endl
//                 << "[7] LZW" << endl
//                 << "[0] Sair" << endl;

//             cout << "Digite uma opcao de menu: ";
//             cin >> option;
//             switch (option)
//             {
//                 case 1:
//                     n = 10;
//                     delete [] vet;
//                     vet = randomTest(n);
//                     printPrompt(vet, n);
//                     break;
//                 case 2:
//                     cout << "Quantos registros deseja importar? ";
//                     cin >> n;
//                     delete [] vet;
//                     vet = import(n);
//                     printPrompt(vet, n);
//                     break;
//                 case 3:
//                     delete arv_vp;
//                     arv_vp = new ArvoreVP();
//                     treeTest(arv_vp, vet, n);
//                     break;
//                 case 4:
//                     delete arv_b;
//                     arv_b = new ArvoreB();
//                     treeTest(arv_b, vet, n);
//                     break;
//                 case 5:
//                     compressTest(0);
//                     break;
//                 case 6:
//                     compressTest(1);
//                     break;
//                 case 7:
//                     compressTest(2);
//                     break;
//                 default:
//                     break;
//             }
//         } while(option != 0);

//         delete [] vet;
//         delete arv_vp;
//         delete arv_b;
//     }

//     return 0;
// }

void estatisticas()
{
    int tam = 10, ordemInicial = 20, ordemFinal = 200;
    int incremento = ceil((ordemFinal - ordemInicial) / (float)tam);
    cout << "VALOR INCREMENTO: " << incremento << endl;

    int ordem[tam + 1];
    int comparacoesBusca[tam + 1];
    int comparacoesInsercao[tam + 1];

    ordem[0] = ordemInicial;

    for (int i = 1; i < tam + 1; i++)
    {
        ordem[i] = ordem[i - 1] + incremento;
    }

    int n = 10;
    int b = 100;

    /*
        Para cada ordem, executa 3 testes de busca e insercao
    */
    for (int o = 0; o < tam; o++)
    {
        cout << "-------------- ORDEM " << ordem[o] << " -------------------------" << endl;

        double mediaComparacoesInsercao = 0.0, mediaComparacoesBusca = 0.0;

        for (int k = 0; k < 3; k++)
        {
            mediaComparacoesInsercao = 0.0;
            mediaComparacoesBusca = 0.0;

            ArvoreB *arv_b = new ArvoreB(ordem[o]);
            ProductReview *vetN;
            ProductReview *vetB;

            cout << "Importando " << n << " registros para inserir na arvore" << endl;
            vetN = import(n);

            cout << "Inserindo " << n << " registros na arvore" << endl;
            for (int i = 0; i < n; i++)
            {
                arv_b->insere(&vetN[i]);
            }

            mediaComparacoesInsercao += arv_b->getCompInsercao();
            cout << "Número de comparações na inserção: " << arv_b->getCompInsercao() << endl;

            cout << "Importando " << b << " registros para buscar na arvore" << endl;
            vetB = import(b);

            cout << "Buscando " << b << " registros na arvore" << endl;
            int countReviewsEncontrados = 0;
            for (int i = 0; i < b; i++)
            {
                ProductReview *p = arv_b->busca(vetB[i].getUserId(), vetB[i].getProductId());
                if (p != NULL)
                {
                    countReviewsEncontrados++;
                }

                delete p;
            }

            mediaComparacoesBusca += arv_b->getCompBusca();
            cout << "Número de comparações na busca de " << b << " registros:  " << arv_b->getCompBusca() << endl;
            cout << "Reviews encontrados: " << countReviewsEncontrados << endl;

            cout << endl
                 << endl;

            delete[] vetN;
            delete[] vetB;
            delete arv_b;
        }

        mediaComparacoesInsercao /= 3.0;
        mediaComparacoesBusca /= 3.0;
        cout << "MÉDIA COMPARACOES INSERCAO: " << mediaComparacoesInsercao << endl;
        cout << "MÉDIA COMPARACOES BUSCA: " << mediaComparacoesBusca << endl;

        comparacoesBusca[o] = mediaComparacoesBusca;
        comparacoesInsercao[o] = mediaComparacoesInsercao;

        cout << "\n\n"
             << endl;

        ofstream saidaCompIns, saidaCompBus;
        saidaCompIns.open("comparacoesInsercao.dat");
        saidaCompBus.open("comparacoesBusca.dat");

        saidaCompIns << 0 << " " << 0 << endl;
        saidaCompBus << 0 << " " << 0 << endl;
        for (int i = 0; i < tam; i++)
        {
            saidaCompIns << ordem[i] << " " << comparacoesBusca[i] << endl;
            saidaCompBus << ordem[i] << " " << comparacoesInsercao[i] << endl;
        }

        saidaCompIns.close();
        saidaCompBus.close();
    }

    system("python plot.py");
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        // OBS.: TODOS OS ARQUIVOS USADOS NO PROGRAMA (TANTO DE ENTRADA QUANTO DE SAÍDA) DEVEM ESTAR LOCALIZADOS NO DIRETÓRIO FORNECIDO
        // PELO USUÁRIO COMO ARGUMENTO DA LINHA DE COMANDO
        std::string path(argv[1]);
        createBinary(path);

        int n = 1000000;
        int b = 100;

        estatisticas();

        return 1;

        // ArvoreB *arv_b = new ArvoreB();
        // for (int i = 10; i <= 30; i++)
        // {
        //     arv_b->insere(new ProductReview(to_string(i), "", "", "", 2));
        // }

        // arv_b->print();

        // delete arv_b;
        // return 0;

        for (int k = 0; k < 3; k++)
        {
            ArvoreB *arv_b = new ArvoreB();
            ProductReview *vetN;
            ProductReview *vetB;

            cout << "Importando " << n << " registros para inserir na arvore" << endl;
            vetN = import(n);

            cout << "Inserindo " << n << " registros na arvore" << endl;
            for (int i = 0; i < n; i++)
            {
                arv_b->insere(&vetN[i]);
            }

            cout << "Número de comparações na inserção: " << arv_b->getCompInsercao() << endl;

            cout << "Importando " << b << " registros para buscar na arvore" << endl;
            vetB = import(b);

            arv_b->setCompBusca(0);
            arv_b->setCompInsercao(0);

            cout << "Buscando " << b << " registros na arvore" << endl;
            int countReviewsEncontrados = 0;
            for (int i = 0; i < b; i++)
            {
                ProductReview *p = arv_b->busca(vetB[i].getUserId(), vetB[i].getProductId());
                if (p != NULL)
                {
                    countReviewsEncontrados++;
                }

                delete p;
            }

            cout << "Número de comparações na busca de " << b << " registros:  " << arv_b->getCompBusca() << endl;
            cout << "Reviews encontrados: " << countReviewsEncontrados << endl;

            cout << endl
                 << endl;

            delete[] vetN;
            delete[] vetB;
            delete arv_b;
        }
    }

    return 0;
}