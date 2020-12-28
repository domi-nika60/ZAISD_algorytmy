// #include <stdio.h>
#include <omp.h>
#include <iostream>

using namespace std;

int main() {

   #pragma omp parallel 
   {
     int k, n;
    n = omp_get_num_threads();
    k = omp_get_thread_num();
   
    cout << "Watkow: " << n << " teraz dziala  " << k << endl;
   }

}