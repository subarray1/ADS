#include <iostream>
using namespace std;

const int MAX_NODES = 100;
const int INF = 999999;

int minDistance(int dist[], bool visited[], int V) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printShortestPaths(int dist[],  int V, int start) {
    cout << "\nShortest paths from node " << start << ":\n";
    for (int i = 0; i < V; i++) {
        if (i != start) {
            cout << "Path to " << i << " (Cost: " << dist[i] << "): ";
            cout << endl;
        }
    }
}

void Dijkstra(int graph[MAX_NODES][MAX_NODES], int V, int startNode) {
    int dist[V];      // Distance from startNode
    bool visited[V];  // If the node is included in shortest path
    int parent[V];    // To store the shortest path tree

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[startNode] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
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

    printShortestPaths(dist,  V, startNode);
}

int main() 
{
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    int graph[MAX_NODES][MAX_NODES] = {0};

    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cout << "Enter edge " << i + 1 << " (u v weight): ";
        cin >> u >> v >> weight;
        graph[u][v] = weight;
        graph[v][u] = weight;  // Remove this line for directed graphs
    }

    int startNode;
    cout << "Enter starting node: ";
    cin >> startNode;
    Dijkstra(graph, V, startNode);
    return 0;
}
