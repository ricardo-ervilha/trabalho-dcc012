#include <iostream>
#include "QuickSort.h"
#include "BucketSort.h"
#include "ArvoreB.h"
#include "ProductReview.h"
#include <sstream>

int main()
{
    ArvoreB *ab = new ArvoreB();
    // ProductReview *teste = ab->busca("1","2");

    Info k, k2;

    string userId = "lucas";
    string productId = "santana";

    k.id = userId + productId;
    k.indexLoc = -1;

    k2.id = "teste";
    k2.indexLoc = -1;

    ab->insert(ab, k);

    ProductReview *teste = ab->busca(userId, productId);
    return 0;
}
