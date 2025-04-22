#include <iostream>
using namespace std;

#define MAX_NODES 100 
class Graph {
    int adj[MAX_NODES][MAX_NODES]; 
    int V;

public:
    Graph(int vertices) {
        V = vertices;
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                adj[i][j] = 0; 

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1; 
    }

    void DFS(int start) {
        int visited[MAX_NODES] = {0}; 
        int stack[MAX_NODES];        
        int top = -1;                 

        stack[++top] = start; 
        visited[start] = 1;   

        while (top >= 0) {
            int node = stack[top--]; 

            cout << node << " ";  

            for (int i = V - 1; i >= 0; i--) {
                if (adj[node][i] == 1 && visited[i] == 0) {
                    stack[++top] = i; 
                    visited[i] = 1;    
                }
            }
        }
    }
};

int main() {
    Graph g(6); // Create a graph with 6 vertices (0 to 5)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    cout << "Depth-First Search starting from node 0: ";
    g.DFS(0); // Perform DFS starting from node 0
    return 0;
}
