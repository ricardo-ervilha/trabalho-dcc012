#ifndef QUICK_H
#define QUICK_H
#include "ProductReview.h"
using namespace std;

class QuickSort{
    private:
        ProductReview *list;
        int registros;
        int RandomPivo(int inicio, int fim);
        int Particiona(ProductReview *list, int inicio, int fim, int Comp_Mov[2]);
        void QuickSortRec(ProductReview *list, int inicio, int fim,int Comp_Mov[2]);
        void Troca(ProductReview i, ProductReview j);
        
        
    public:
        QuickSort();
        QuickSort(ProductReview *, int);
        ~QuickSort();
        void sort();
        void imprime();
};

#endif