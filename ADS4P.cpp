#include <iostream>
using namespace std;

const int MAX_NODES = 100;
const int INF = 999999;

void printMST(int parent[],int graph[MAX_NODES][MAX_NODES], int V) 
{
    int totalCost = 0;
    cout << "Minimum Spanning Tree (MST):\n";
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
        totalCost += graph[i][parent[i]];
    }
    cout << "Total cost of MST: " << totalCost << endl;
}

int minKey(int key[], bool visited[], int V) 
{
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++) 
    {
        if (!visited[v] && key[v] < min) 
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void PrimMST(int graph[MAX_NODES][MAX_NODES], int V, int startNode) {
    int parent[V];   
    int key[V];      
    bool visited[V];  

   
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        visited[i] = false;
        parent[i] = -1;
        
    }

    key[startNode] = 0;     
    parent[startNode] = -1;  

    for (int i = 0; i < V - 1; i++) 
    {
        int u = minKey(key, visited, V);
        if (u == -1) break;  
        visited[u] = true;

        for (int i = 0; i < V; i++) {
            if (graph[u][i] && !visited[i] && graph[u][i] < key[i]) {
                parent[i] = u;
                key[i] = graph[u][i];
            }
        }
    }  
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    printMST(parent, graph, V);
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    int graph[MAX_NODES][MAX_NODES] = {0};
    int u, v, weight;

    for (int i = 0; i < E; i++) {       
        cout << "Enter edge " << i + 1 << " (u v weight): ";
        cin >> u >> v >> weight;
        graph[u][v] = weight;
        graph[v][u] = weight;  
    }

    int startNode;
    cout << "Enter starting node: ";
    cin >> startNode;



    PrimMST(graph, V, startNode);
    return 0;
}

