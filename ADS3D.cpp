#include <iostream>
using namespace std;

#define MAX_NODES 100 // Maximum number of nodes

class Graph {
    int adj[MAX_NODES][MAX_NODES]; // Adjacency matrix
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
        adj[v][u] = 1; // For undirected graph
    }

    void DFS(int start) {
        int visited[MAX_NODES] = {0}; // Initialize visited array
        int stack[MAX_NODES];         // Stack to store nodes for DFS
        int top = -1;                 // Stack pointer

        stack[++top] = start; // Push the start node onto the stack
        visited[start] = 1;   // Mark the start node as visited

        while (top >= 0) {
            int node = stack[top--]; // Pop from stack

            cout << node << " ";  // Print the current node

            // Push all unvisited neighbors in reverse order (for correct DFS order)
            for (int i = V - 1; i >= 0; i--) {
                if (adj[node][i] == 1 && visited[i] == 0) {
                    stack[++top] = i; // Push the unvisited neighbor onto the stack
                    visited[i] = 1;    // Mark the neighbor as visited
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