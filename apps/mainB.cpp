#include <iostream>
#include "QuickSort.h"
#include "BucketSort.h"
#include "ArvoreB.h"
#include "ProductReview.h"
#include <sstream>

int main()
{
    //o valor minimo da ordem é 4
    //ordem 4 em termos de grau minimo significa que terei t=2, ou seja maximo 4 filhos e 3 chaves por nó
    ArvoreB *ab = new ArvoreB(4);
    
    for (int i = 0; i < 20; i++)
    {
        ab->insert(ab, {i+1,-1});
    }
        
    ab->print();

    //ProductReview *teste = ab->busca(userId, productId);
    
    return 0;
}
