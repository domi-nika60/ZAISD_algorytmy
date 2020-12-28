#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <math.h>       /* sqrt */
#include <random>

using namespace std;

double dist(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double get_rand(double max) {
    return ((double) rand() / RAND_MAX) * max;
}

int main(){
    long probek = 100000000;
    long out = 0;
    int r = 1;

    double start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:out)
        for (long i = 0; i < probek; i++) {
            double a = get_rand(r);
            double b = get_rand(r);
            if (dist(r, r, a, b) > r) {
                out++;
            }
        }
    double stop_time = omp_get_wtime();
    
    long in = probek-out;
    double pi = 4 * ((double) in / (double) probek);

    cout << "Pi: " <<  pi << endl;
    cout << "Czas: " << stop_time- start_time << " s " << endl;
    cout << "Probek: " << probek << ", w srodku: " << in << ", na zewnatrz: " << out << endl; 

}