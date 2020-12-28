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

bool bfs(int **rGraph, int s, int t, int parent[], int cols)
{
    bool visited[cols];
    memset(visited, 0, sizeof(visited));
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < cols; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}

int fordFulkerson(int **graph, int s, int t, int cols)
{
    int u, v;

    int parent[cols];
    int max_flow = 0;
    while (bfs(graph, s, t, parent, cols))
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
            // graph[v][u] += path_flow;  
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
    std::ifstream is("tab.txt");

    // load the matrix
    std::vector< std::vector<int> > matrix;
    load_matrix(&is, &matrix);

    int connection = matrix.size();
    cout << "CONNECTION_SIZE: " << connection << endl;
    int rows = matrix[0][0];
    cout << "ROWS: " << rows << endl;
    int cols = 3;

    int **graph = new int*[rows];

    for(int r =0; r<rows;r++)
    {
        graph[r] = new int[rows];
    }

    for(int i=1; i<connection; i++){
        for(int j=0; j<cols; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<rows; j++){
            graph[i][j] = 0;
        }
    }

    for(int i=1; i<connection; i++){
            graph[matrix[i][0]][matrix[i][1]] = matrix[i][2];
    }

    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, rows-1, rows);
    // getch();


    return 0;
}
