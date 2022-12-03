#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <time.h>
#include "ProductReview.h"
#include "File.h"
#include <chrono>
#include "HashProduct.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "BucketSort.h"
#include <fstream>
#include "ArvoreVP.h"

int main(){


    File* arq = new File("/home/ricardo/dcc-012/trabalho-dcc012/");
    
    ArvoreVP *tree = new ArvoreVP();
    
    ProductReview *list = arq->import(3);

    tree->insere(&list[0]);
    tree->insere(&list[1]);
    tree->insere(&list[2]);
    
    tree->print();
}