#ifndef MERGESORT_H
#define MERGESORT_H
#include "ProductReview.h"
using namespace std;

class MergeSort{
    private:
        ProductReview *list;
        int registros;
        void MergeSortRec(ProductReview *list, ProductReview *Aux, int inicio, int fim,int Comp_Mov[2]);
        void Merge(ProductReview *list, ProductReview *Aux, int inicio, int meio, int fim, int Comp_Mov[2]);
        
    public:
        MergeSort();
        MergeSort(ProductReview *, int);
        ~MergeSort();
        void sort();
        void imprime();
};

#endif