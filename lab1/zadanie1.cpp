#include <iostream>

using namespace std;

int main() {

    // graf skierowany z ujemnymi krawędziami w postaci macierzy
    int BF_array [5][5] = {
       { 999, 999, 999, 999, 999 },
       { 2,   999, 1,   999, 999 },
       { 999, 2,   999, 999, -3  },
       { 999, 999, 1,   999, 2   },
       { 3,   2,   999, 999, 999 }, 
    };

    // ilość węzłów:
    const int dl = 5;

    // wektor odległości do każdego z węzłów
    int d[dl] = {0, 999, 999, 999, 999};
    // wektor najkrótszej ścieżki
    int pi[dl];
    //wartość węzła dla którego sprawdzam najkrótsza ścieżkę:
    int cel=3;

    // relaksacja 
    for (int i=0; i<(dl-1); i++ ){
        // for each (u,v) c E
        for (int v=0; v<dl; v++){
            for (int u=0; u<dl; u++){
                if ( d[u]>(d[v] + BF_array[u][v])){
                    // uaktualnienie d z najkrótsza sciezka
                    d[u]=(d[v] + BF_array[u][v]);
                    pi[u] = v;
                }
            }
        }
    }

    // znajdowanie ujemnych ścieżek
    for (int i=0; i<(dl-1); i++ ){
        // for each (u,v) c E
        for (int v=0; v < dl; v++){
            for (int u=0; u < dl; u++){
                if ( d[u]>(d[v] + BF_array[u][v])){
                    cout << "Znaleziono cykl ujemny!" << endl;
                    d[u]=-999;
                }
            }
        }
    }

    //wypisanie długości najkrótszej drogi do każdego węzła z pierwszego
    for ( int i=0; i<dl; i++){
        cout << "Do węzła: " << i << " wartość wynosi: " << d[i] << endl;
    }

    //najkrótsza ścieżka:
    cout << "sciezka z punktu " << cel << " do punktu 0: " << endl;
    while(cel!=0){
        cout << " "<< pi[cel];
        cel = pi[cel];
    }
}