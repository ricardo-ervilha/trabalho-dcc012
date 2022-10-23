#include <iostream>
#include "Hash.h"
#include <cstdlib>
#include <ctime>
#include "File.h"
#include "ProductReview.h"
#include <chrono>

using namespace std;

//melhorar a funcao de hash
//para melhorar o espalhamento dos valores 
//e por consequencia reduzir o tempo de busca.

int main(void){
    
    File* importacao = new File();

    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    ProductReview *teste = importacao->import(10000);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  
    std::cout << "Tempo(Chrono): " << elapsed_seconds.count() << "s\n";
}