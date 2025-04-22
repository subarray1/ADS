#include <iostream>
using namespace std;

#define MAX_NODES 100 // Maximum number of nodes

class Graph 
{
    int adj[MAX_NODES][MAX_NODES]; // The adjacency matrix to store connections.
    int V; // Number of vertices

    public:
    Graph(int vertices) {
        V = vertices;
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                adj[i][j] = 0; // Initialize all edges to 0
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1; // For undirected graph (remove for directed)
    }

    void BFS(int start) {
        int visited[MAX_NODES] = {0}; // Track visited nodes
        int queue[MAX_NODES]; // Queue for BFS
        int front = 0, rear = 0;

        visited[start] = 1;
        queue[rear++] = start; // Enqueue start node

        while (front < rear) {
            int node = queue[front++]; // Dequeue
            cout << node << " ";

            for (int i = 0; i < V; i++) {
                if (adj[node][i] == 1 && visited[i] == 0) {
                    visited[i] = 1;
                    queue[rear++] = i; // Enqueue unvisited neighbor
                }
            }
        }
    }
};

int main()
{
    Graph g(6); // Create a graph with 6 vertices (0 to 5)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    cout << "Breadth-First Search starting from node 0: ";
    g.BFS(0);
    return 0;
}