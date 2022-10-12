#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include "ProductReview.h"

class No
{
private:
    ProductReview* info; /// valor armazenado no No
    No *prox; /// ponteiro para o proximo No
public:
    No()                  {};
    ~No()                 { };
    ProductReview* getInfo()         { return info; };
    No* getProx()         { return prox; };
    void setInfo(ProductReview* val) { info = val; };
    void setProx(No *p)   { prox = p; };
};
#endif // NO_H_INCLUDED