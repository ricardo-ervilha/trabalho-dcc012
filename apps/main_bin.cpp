#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <time.h>
#include "ProductReview.h"
#include "ListaEncad.h"
#include "File.h"
#include <chrono>

//verificar consumo de memoria durante geração do arquivo
//talvez esteja faltando deletar parte de algo

using namespace std;

int main(){
    File* file = new File();


    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
    file->makeBinaryFile();

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  
    std::cout << "Tempo(Usando a Chrono): " << elapsed_seconds.count() << "s\n";
    
    
    cout << "Buscando review 6784921" << endl;
    cout << "Valor dele no csv: " << "AM16OYD1Q7Z06,B009YWN926,3.0,1405382400" << endl;
    cout << "Valor dele na getReview: ";
    file->getReview(6784921);
    
    return 0;
}