#include <iostream>
using namespace std;

struct Edge {
    int src, dest, weight;
};

int findParent(int parent[], int v) {
    if (parent[v] == v)
        return v;
    return findParent(parent, parent[v]);
}

void unionSets(int parent[], int u, int v) {
    int pu = findParent(parent, u);
    int pv = findParent(parent, v);
    parent[pu] = pv;
}

void kruskalMST(Edge edges[], int V, int E) {
    int parent[10];         
    Edge mst[10];          
    int count = 0;          

   
    for (int i = 0; i < V; i++)
        parent[i] = i;

   
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

   
    for (int i = 0; i < E && count < V - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        
        if (findParent(parent, u) != findParent(parent, v)) {
            mst[count] = edges[i];
            count++;
            unionSets(parent, u, v);
        }
    }

   
    cout << "\nMinimum Spanning Tree:\n";
    for (int i = 0; i < count; i++) {
        cout << mst[i].src << " - " << mst[i].dest << " : " << mst[i].weight << endl;
    }
}


int main() {
    int V = 4, E = 5;
    Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(edges, V, E);
    return 0;
}
