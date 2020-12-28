#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <queue>
#include <conio.h>
#include <climits>

using namespace std;
// #define V 6

bool bfs(int **rGraph, int s, int t, int parent[], const int V)
{
    //tworzy tablice odwiedzonych wierzcholkow 
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    queue <int> q;
    q.push(s);
    visited[s] = true; //pierwszy node jako odwiedzony
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);  // zwraca true gdy osiąga ostatni node ze źródła
}

//zwraca maksymalny przeplyw z s do t w danym grafie (V - liczba nodów)
int fordFulkerson(int **graph, int s, int t, int V)
{
    int u, v;

    int parent[V]; //przechowuje ścieżkę z bfs
    int max_flow = 0;

    //dopóki istanieje możliwa ścieżka
    while (bfs(graph, s, t, parent, V))
    {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, graph[u][v]);
        }
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            graph[u][v] -= path_flow;
            graph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

void load_matrix(std::istream* is,
        std::vector< std::vector<int> >* matrix,
        const std::string& delim = " \t")
{
    using namespace std;
    string      line;
    string      strnum;

    // clear first
    matrix->clear();

    // parse line by line
    while (getline(*is, line))
    {
        matrix->push_back(vector<int>());

        for (string::const_iterator i = line.begin(); i != line.end(); ++ i)
        {
            // If i is not a delim, then append it to strnum
            if (delim.find(*i) == string::npos)
            {
                strnum += *i;
                if (i + 1 != line.end()) // If it's the last char, do not continue
                    continue;
            }
            // if strnum is still empty, it means the previous char is also a
            // delim (several delims appear together). Ignore this char.
            if (strnum.empty())
                continue;

            // If we reach here, we got a number. Convert it to double.
            int       number;

            istringstream(strnum) >> number;
            matrix->back().push_back(number);

            strnum.clear();
        }
    }
}

#include <fstream>
#include <iostream>

int main()
{
    using namespace std;

    // read the file
    std::ifstream is("macierz.txt");

    // load the matrix
    std::vector< std::vector<int> > matrix;
    load_matrix(&is, &matrix);

    int rows = matrix.size();
    const int cols = matrix[0].size();
    cout << "SIZE OF ARRAY: " << cols << endl;

    int **graph = new int*[cols];
    for(int r =0; r<rows;r++)
    {
        graph[r] = new int[cols];
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            graph[i][j] = matrix[i][j];
        }
    }

    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, rows-1, cols);
    // getch();


    return 0;
}
