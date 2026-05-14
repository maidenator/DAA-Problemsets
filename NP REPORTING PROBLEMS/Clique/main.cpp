#include <iostream>
#include <algorithm>
using namespace std;

int n, edges, maxCliqueSize = 0;
int graph[20][20] = {0};
int currentClique[20];

// Checks if node 'v' is connected to every member already in the current clique
bool isSafe(int v, int size) {
    for (int i = 0; i < size; i++) {
        if (graph[v][currentClique[i]] == 0) return false;
    }
    return true;
}

void solve(int startNode, int size) {
    // Every time we find a valid clique, check if it's the largest
    if (size > maxCliqueSize) maxCliqueSize = size;

    for (int i = startNode; i < n; i++) {
        if (isSafe(i, size)) {
            currentClique[size] = i; // Add to club
            solve(i + 1, size + 1);  // Try to find more members
            // No need to "undo" currentClique[size] because we just overwrite it
        }
    }
}

int main() {
    cout << "Nodes and Edges: "; cin >> n >> edges;

    for (int i = 0, u, v; i < edges; i++) {
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }

    // Start looking for cliques from node 0
    solve(0, 0);

    cout << "Maximum Clique Size: " << maxCliqueSize << endl;

    return 0;
}