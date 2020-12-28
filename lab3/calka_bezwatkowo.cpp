#include <iostream>
#include <cstdlib>
#include <time.h>
#include <thread>
#define CLOCKS_PER_SEC ((clock_t)1000)

using namespace std;

double fd(double x) { return 4*(1/(x*x + 1)); }

int main()
{
    double xp, xk, calka;
    double dx = 0.000000001;

    xp = 0;
    xk = 1;
    double rectangle = (xk - xp) / dx;

    cout << "kroki: " << rectangle << endl;
    calka = 0;

    clock_t START_TIMER = clock();
    for (double i=1; i<=rectangle; i++)
    {
        calka += fd(xp + i*dx)*dx;
    }

    cout << "Wynik: " <<  calka << endl;
    cout << "Czas: " << float(clock() - START_TIMER) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}