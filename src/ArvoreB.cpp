#include "ArvoreB.h"

extern string path;

ArvoreB::ArvoreB()
{
    cout << "Criando árvore B...." << endl;
    /*
        Ordem par para que tenha sempre um número impar de chaves no nó
        Ao subir a chave para o nó pai, sobe sempre o do meio
    */
    this->ordem = 20; // sempre usar ordem par ==> grau minimo t = 2 -> máximo filhos = 4
    this->raiz = new NoB(ordem);
}

ArvoreB::~ArvoreB()
{
}

// /*
//     retorna NULL se a chave foi encontrada na arvore
//     Ou retorna o no folha
// */
// NoB *ArvoreB::encontrarFolha(string keySearch)
// {
//     NoB *p = raiz;
//     bool found = false;
//     NoB *folha = NULL; // aponta para o nó encontrado ou ultimo no pesquisado que deve ser uma folha
//     int ki;            // posião da chave dentro do nó ou posição onde a chave deve ser inserida

//     while (p != NULL)
//     {
//         int i = 0;
//         ki = 0;
//         folha = p;

//         while (i < p->n)
//         {

//             if (keySearch > p->chaves[i].id)
//             { // continua procurando no mesmo nó
//                 i++;
//                 ki = i;
//             }
//             else if (keySearch == p->chaves[i].id)
//             {
//                 found = true; // inserção inválida
//                 p = NULL;

//                 return NULL;
//             }
//             else
//             { // pega o próximo nó
//                 p = p->filhos[i];
//                 i = p->n + 1;
//             }
//         }

//         if (i == p->n)
//         {
//             p = p->filhos[i];
//         }
//     }

//     return folha; // retorna a folha onde deve ser inserida a chave
// }

// ProductReview *ArvoreB::busca(string userId, string productId)
// {
//     return auxBusca(userId + productId, raiz);
// }

// ProductReview *ArvoreB::auxBusca(string k, NoB *no)
// {
//     if (no != NULL)
//     {
//         int i;
//         for (i = 1; i <= no->n && no->chaves[i - 1].id < k; i++)
//             ;

//         // se i>no->n significa que a chave está no filho direita, entra no if
//         // se no->chaves[i - 1].id > k significa que a chave está no filho a esquerda, entra no if

//         // se !(i>no->n) && !(no->chaves[i - 1].id > k) e pelo for anterior !(no->chaves[i - 1].id < k),
//         // então a chave está no próprio no, na posição [i-1] , entra no else

//         if (i > no->n || no->chaves[i - 1].id > k)
//         {
//             return auxBusca(k, no->filhos[i - 1]);
//         }
//         else
//         {
//             // return no->chaves[i - 1].indexLoc; // buscar no arquivo
//             return NULL;
//         }
//     }
//     else
//     {
//         return NULL;
//     }
// }

// void ArvoreB::insere(ProductReview *pr)
// {
//     Info novoInfo;
//     novoInfo.id = pr->getUserId() + pr->getProductId();
//     novoInfo.indexLoc = pr->getLocal();

//     // encontrar um nó folha para inserir a chave
//     NoB *folha = encontrarFolha(novoInfo.id);

//     if (folha != NULL)
//     {
//         while (true)
//         {
//             int i;
//             for (i = 0; i < folha->n && folha->chaves[i].id < novoInfo.id; i++)
//                 ;

//             if (i < folha->n) // nó não está cheio
//             {
//                 // insere a chave e aumenta o n
//                 folha->chaves[i] = novoInfo;
//                 folha->n = folha->n + 1;
//                 return;
//             }
//             else
//             {
//                 NoB *novo = folha->cisao(novoInfo);

//                 novoInfo = folha->chaves[folha->n - 1]; // pegar a info a ser promovida

//                 if (folha == raiz)
//                 {
//                     /*
//                         se o no que sofreu cisao for uma raiz
//                             - cria uma nova raiz
//                             - coloca chave mediana na nova raiz
//                             - faz os filhos apontarem para a folha a novo no
//                     */
//                     NoB *novaRaiz = new NoB();
//                     novaRaiz->chaves[0] = novoInfo; // posição 0
//                     novaRaiz->filhos[0] = folha;    // filho esquerda
//                     novaRaiz->filhos[1] = novo;     // filho a direita
//                     novaRaiz->n = 1;
//                     novaRaiz->ehFolha = false;
//                     raiz = novaRaiz;
//                     return;
//                 }
//                 else
//                 {
//                 }
//             }
//         }
//     }
//     else
//     {
//         cout << "Valor já está na arvore" << endl;
//     }
// }

ProductReview *ArvoreB::busca(string userId, string productId)
{
    Info k;
    k.id = userId + productId;
    k.indexLoc = -1;

    if (search(raiz, &k) == NULL)
    {
        return NULL;
    }
    File *arq = new File(path);
    ProductReview pr = arq->converteReview(k.indexLoc);
    ProductReview *prAux = new ProductReview(pr.getUserId(), pr.getProductId(), pr.getTimeStamp(), pr.getRating(), pr.getLocal());
    return prAux;
}

/*
    A entrada é um ponteiro para o nó raiz e a chave k a ser procurada
    Se for encontrado o registro, guarda a localização no arquivo, no atributo indexLoc de k
*/
NoB *ArvoreB::search(NoB *x, Info *k)
{
    if (x != NULL)
    {
        int i;
        for (i = 0; i < x->n && x->chaves[i].id < (*k).id; i++)
            ;

        /*
            if i==n e não for folha tenho que pegar os filhos na posição i
        */
        if (i < x->n && (*k).id == x->chaves[i].id)
        {
            (*k).indexLoc = x->chaves[i].indexLoc;
            return x;
        }
        else if (x->ehFolha)
        {
            return NULL;
        }
        else
        {
            // DISK-READ (x->filhos[i])
            return search(x->filhos[i], k);
        }
    }
    else
    {
        return NULL;
    }
}

/*
    Função obrigatória, exigida pelo traalho
*/
void ArvoreB::insere(ProductReview *pr)
{
    if (pr == NULL)
    {
        cout << "Erro ao tentar inserir um registro NULL na árvore...." << endl;
        cout << "Talvez você não tenha importado os registros na opção 2...." << endl;
        return;
    }
    Info info = {pr->getUserId() + pr->getProductId(), pr->getLocal()};

    this->insert(this, info);
}

/*
    inserindo uma chave em uma unica passagem descendente pela arvore
    usa cisão na descida para garantir que sempre tera um no com espaço vazio no caminho de inserção
*/
void ArvoreB::insert(ArvoreB *T, Info k)
{
    // inserção do primeiro registo na arvore
    if (T->raiz->n == 0)
    {
        raiz->chaves[0] = k;
        raiz->n = raiz->n + 1;
        return;
    }

    NoB *r = T->raiz;

    // se a raiz esta cheia, a raiz é repartida e um novo nó s, que tem 2 filhos, se torna raiz
    if (r->cheio())
    {
        NoB *s = new NoB(this->ordem);

        T->raiz = s; // a raiz da arvore agora é s
        s->ehFolha = false;
        s->n = 0;

        s->filhos[0] = r; // a antiga raiz agora é filho de s

        /*
            Antes de inserir a chave, faço o split, de forma que sobe para o pai o nó intermediário
            passo o 0 para pegar o filho na posição 0 de s
            na função split pego o filho de s na posição 0, que é a raiz antiga (cheia) que acabei de add como filho de s
        */
        splitChild(s, 0);
        insertNonFull(s, k);
    }
    else
    {
        insertNonFull(r, k);
    }
}

/*
    Toma como entrada um nó interno x não cheio e um índice i tal que x->filhos[i] é um filho cheio de x
    Reparte o filho em dois e ajusta x de modo que tenha mais um filho
    x é o nó não cheio que está sendo repartido (x precisa não estar cheio pois vai ganhar mais uma chave e um ponteiro pra um novo filho)
    i é o indice do filho de x que está cheio
    y é o i-ésimo filho de x que está cheio
    nó y tem originalmente n filhos e é reduzido para [n/2] filhos
*/
void ArvoreB::splitChild(NoB *x, int i)
{
    NoB *z = new NoB(this->ordem); // novo nó que ira receber as chaves de y

    NoB *y = x->filhos[i]; // filho de x

    z->ehFolha = y->ehFolha;

    int qtd = ceil(y->n / 2.0);
    z->n = qtd - 1;

    // copia as qtd maiores chaves de y para z
    for (int j = 0; j < qtd - 1; j++)
    {
        z->chaves[j] = y->chaves[j + qtd];
    }

    // copia os filhos correspondentes de y para z
    if (!y->ehFolha)
    {
        for (int j = 0; j < qtd; j++)
        {
            z->filhos[j] = y->filhos[j + qtd]; // pega de qtd em diante
        }
    }

    // y agora tem qtd-1 chaves
    y->n = qtd - 1;

    // desloca 1 posição para direita até i para posicionar o novo filho
    for (int j = x->n; j >= i + 1; j--)
    {
        x->filhos[j + 1] = x->filhos[j];
    }

    // coloca o novo filho (z) em x
    x->filhos[i + 1] = z;

    // desloca uma posição para direita até i para posionar nova chave
    for (int j = x->n - 1; j >= i; j--)
    {
        x->chaves[j + 1] = x->chaves[j];
    }

    // x recebe a chave mediana de y
    x->chaves[i] = y->chaves[qtd - 1];

    // atualiza a quantidade de chaves de x
    x->n = x->n + 1;

    // DISK-WRITE(y)
    // DISK-WRITE(z)
    // DISK-WRITE(x)
}

/*
    insere a chave k no nó x que supostamente não está cheio quando a função é chamada

*/
void ArvoreB::insertNonFull(NoB *x, Info k)
{
    int i = x->n - 1; // percorrer da ultima posição ocupada até o inicio do nó
    if (x->ehFolha)
    {
        while (i >= 0 && k.id < x->chaves[i].id)
        {
            x->chaves[i + 1] = x->chaves[i];
            i--;
        }

        x->chaves[i + 1] = k;
        x->n = x->n + 1;
        // DISK-WRITE(X)
    }
    else
    {
        while (i >= 0 && k.id < x->chaves[i].id)
        {
            i--;
        }
        i++;
        // DISK-READ (x.filhos[i])
        if (x->filhos[i]->cheio())
        {
            splitChild(x, i);
            if (k.id > x->chaves[i].id)
            {
                i++;
            }
        }
        insertNonFull(x->filhos[i], k);
    }
}

void ArvoreB::print()
{
    cout << "CHAVES NA ARVORE: " << endl;
    auxPrint(raiz);
    cout << endl;
}

void ArvoreB::auxPrint(NoB *no)
{
    // cout << "Número de chaves no nó: " << no->n << endl;
    if (no->n > 0)
    {
        if (!no->ehFolha)
        {
            for (int i = 0; i < no->n + 1; i++)
            {
                auxPrint(no->filhos[i]);
                no->printKey(i);
            }
        }
        else
        {
            no->printKeys();
        }
    }
}