#include <iostream>

using namespace std;

int main() {

    // graf skierowany z ujemnymi krawędziami w postaci tablicy (U V W)
    int BF_table[8][3] = 
    {
        {0, 1, 2},
        {1, 2, 2},
        {2, 1, 1},
        {2, 3, 1},
        {1, 4, 2},
        {4, 2, -3},
        {0, 4, 3},
        {4, 3, 2},
    };

    //ilość węzłów:
    const int dl = 5;
    //ilość krawędzi:
    const int e = 8;

    // wektor odległości do każdego z węzłów
    int d[dl] = {0, 999, 999, 999, 999};
    // wektor najkrótszej ścieżki
    int pi[dl];
    //wartość węzła dla którego sprawdzam najkrótsza ścieżkę:
    int cel=3;

    // relaksacja 
    for (int i=0; i<(dl-1); i++ ){
        for (int j=0; j<e; j++){
            if ( d[BF_table[j][1]] > (BF_table[j][2] + d[BF_table[j][0]])){
                // uaktualnienie d z najkrótsza sciezka
                // u = BF_table[j][1], v = BF_table[j][0], BF_array[u][v]= BF_table[j][2]
                d[BF_table[j][1]]=(d[BF_table[j][0]] + BF_table[j][2]);
                pi[BF_table[j][1]] = BF_table[j][0];
            }
        }
    }

    // znajdowanie ujemnych ścieżek
    for (int i=0; i<(dl-1); i++ ){
        for (int j=0; j<e; j++){
            if ( d[BF_table[j][1]] > (BF_table[j][2] + d[BF_table[j][0]])){
                cout << "Znaleziono cykl ujemny!" << endl;
                d[BF_table[j][1]]=-999;
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