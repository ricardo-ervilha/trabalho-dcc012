#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <time.h>
#include "ProductReview.h"
#include "ListaEncad.h"
#include "File.h"

using namespace std;

int main(){
    File* file = new File();

    file->makeBinaryFile();
    file->getReview(5000003);
    return 0;
}