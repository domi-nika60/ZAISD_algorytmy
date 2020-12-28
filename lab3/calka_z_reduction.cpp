#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

double fd(double x) { return 4*(1/(x*x + 1)); }

int main()
{
    double xp, xk, wynik;
    double dx =  0.000000001;
    xp = 0;
    xk = 1;

    long rectangle = (xk - xp) / dx;
    cout << "kroki: " << rectangle << endl;
    wynik = 0;

    double start_time = omp_get_wtime();
    #pragma omp parallel for reduction (+ : wynik)
        for (long i=0; i < rectangle; i++)
        {
            wynik += fd(xp + i*dx)*dx;
        }

    double stop_time = omp_get_wtime();
    cout << "Wynik: " <<  wynik << endl;
    cout << "Czas = " << stop_time- start_time << " s " << endl;

    return 0;
}