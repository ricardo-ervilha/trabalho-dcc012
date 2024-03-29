#ifndef MERGESORT_H
#define MERGESORT_H
#include "ProductReview.h"
using namespace std;

class MergeSort{
    private:
        ProductReview *list;
        int *Comp_Mov;
        int registros;
        void MergeSortRec(ProductReview *list, ProductReview *Aux, int inicio, int fim);
        void Merge(ProductReview *list, ProductReview *Aux, int inicio, int meio, int fim);
        
    public:
        int * getCompMov() 
        {
            return Comp_Mov;
        }
        MergeSort();
        MergeSort(ProductReview *, int);
        ~MergeSort();
        void sort();
        void imprime();
};

#endif