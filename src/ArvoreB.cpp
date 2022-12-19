#include "ArvoreB.h"

ArvoreB::ArvoreB()
{
    raiz = NULL;
}
ArvoreB::~ArvoreB()
{
}

/*
    retorna NULL se a chave foi encontrada na arvore
    Ou retorna o no folha
*/
NoB *ArvoreB::encontrarFolha(string keySearch)
{
    NoB *p = raiz;
    bool found = false;
    NoB *folha = NULL; // aponta para o nó encontrado ou ultimo no pesquisado que deve ser uma folha
    int ki;            // posião da chave dentro do nó ou posição onde a chave deve ser inserida

    while (p != NULL)
    {
        int i = 0;
        ki = 0;
        folha = p;

        while (i < p->n)
        {

            if (keySearch > p->chaves[i].id)
            { // continua procurando no mesmo nó
                i++;
                ki = i;
            }
            else if (keySearch == p->chaves[i].id)
            {
                found = true; // inserção inválida
                p = NULL;

                return NULL;
            }
            else
            { // pega o próximo nó
                p = p->filhos[i];
                i = p->n + 1;
            }
        }

        if (i == p->n)
        {
            p = p->filhos[i];
        }
    }

    return folha; // retorna a folha onde deve ser inserida a chave
}

ProductReview *ArvoreB::busca(string userId, string productId)
{
    return auxBusca(userId + productId, raiz);
}

ProductReview *ArvoreB::auxBusca(string k, NoB *no)
{
    if (no != NULL)
    {
        int i;
        for (i = 1; i <= no->n && no->chaves[i - 1].id < k; i++)
            ;

        // se i>no->n significa que a chave está no filho direita, entra no if
        // se no->chaves[i - 1].id > k significa que a chave está no filho a esquerda, entra no if

        // se !(i>no->n) && !(no->chaves[i - 1].id > k) e pelo for anterior !(no->chaves[i - 1].id < k),
        // então a chave está no próprio no, na posição [i-1] , entra no else

        if (i > no->n || no->chaves[i - 1].id > k)
        {
            return auxBusca(k, no->filhos[i - 1]);
        }
        else
        {
            return no->chaves[i - 1].indexLoc; // buscar no arquivo
        }
    }
    else
    {
        return NULL;
    }
}

void ArvoreB::insere(ProductReview *pr)
{
    Info novoInfo;
    novoInfo.id = pr->getUserId() + pr->getProductId();
    novoInfo.indexLoc = pr->getLocal();

    // encontrar um nó folha para inserir a chave
    NoB *folha = encontrarFolha(novoInfo.id);

    if (folha != NULL)
    {
        while (true)
        {
            int i;
            for (i = 0; i < folha->n && folha->chaves[i].id < novoInfo.id; i++)
                ;

            if (i < folha->n) // nó não está cheio
            {
                // insere a chave e aumenta o n
                folha->chaves[i] = novoInfo;
                folha->n = folha->n + 1;
                return;
            }
            else
            {
                NoB *novo = folha->cisao(novoInfo);
                
                novoInfo = folha->chaves[folha->n];//pegar a info a ser promovida

                if (folha == raiz)
                {
                    /*
                        se o no que sofreu cisa for uma raiz
                            - cria uma nova raiz
                            - coloca chave mediana na nova raiz
                            - faz os filhos apontarem para a folha a novo no
                    */
                    NoB *novaRaiz = new NoB();
                    novaRaiz->chaves[0] = novoInfo;//posição 0
                    novaRaiz->filhos[0] = folha;//filho esquerda
                    novaRaiz->filhos[1] = novo;//filho a direita
                    novaRaiz->n = 1;
                    novaRaiz->ehFolha = false;
                    raiz = novaRaiz;

                }
            }
        }
    }
    else
    {
        cout << "Valor já está na arvore" << endl;
    }
}
