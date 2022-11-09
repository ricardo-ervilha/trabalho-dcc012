#ifndef NOPRODUCT_H_INCLUDED
#define NOPRODUCT_H_INCLUDED

#include "ProductReview.h"

class NoProductReview
{
private:
    ProductReview info; /// valor armazenado no No
    NoProductReview *prox; /// ponteiro para o proximo No
public:
    NoProductReview()                  {};
    ~NoProductReview()                 { };
    ProductReview getInfo()         { return info; };
    NoProductReview* getProx()         { return prox; };
    void setInfo(ProductReview val) { info = val; };
    void setProx(NoProductReview *p)   { prox = p; };
};
#endif // NO_H_INCLUDED