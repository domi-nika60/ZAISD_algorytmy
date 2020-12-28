#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

double fd(double x) { return 4*(1/(x*x + 1)); }

int main()
{
    double xp, xk;
    double dx = 0.000000001;
    xp = 0;
    xk = 1;

    long rectangle = (xk - xp) / dx;
    cout << "kroki: " << rectangle << endl;
 
    // calka = 0;
    double war [256];

    double start_time = omp_get_wtime();
    #pragma omp parallel 
   {    
        double calka=0;
        int k, n;
        n = omp_get_num_threads();
        k = omp_get_thread_num();
   
        cout << n << "   " << k << endl;
        for (long i=k; i<rectangle; i+=n)
        {
            calka += fd(i*dx)*dx;
        }   
        war[k] = calka;
   }
   double stop_time = omp_get_wtime();

    double res = 0;
    for(int i=0; i<8; i++)
        {
            res +=war[i];
            cout << "Element " <<  i << " to " <<  war[i] << endl;
        }   


    cout << "Wynik: " << res << endl;
    cout << "Czas = " << stop_time- start_time << " s " << endl;
    return 0;
}