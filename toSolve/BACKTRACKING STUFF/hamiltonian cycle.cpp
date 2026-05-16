#include <iostream>
#include <cstring> // For memset
using namespace std;

int n, edges;
int graph[20][20] = {0};
int dp[1 << 20][20]; // Bitmask state cache: dp[visited_mask][current_node]

bool solve(int mask, int pos) {
    // Base Case: If all nodes are visited, check if an edge exists back to start (node 0)
    if (mask == (1 << n) - 1) return graph[pos][0];

    // Memory Guard: If this exact state was already evaluated, return the cached result
    if (dp[mask][pos] != -1) return dp[mask][pos];

    for (int i = 0; i < n; i++) {
        // If edge exists and node 'i' has not been visited yet
        if (graph[pos][i] && !(mask & (1 << i))) {
            if (solve(mask | (1 << i), i))
                return dp[mask][pos] = 1; // Cache success path and return
        }
    }
    return dp[mask][pos] = 0; // Cache failure path if no cycles originate from here
}

int main() {
    cout << "N, Edges: "; cin >> n >> edges;
    for (int i = 0, u, v; i < edges; i++) {
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }

    // One-line initialization: Fill cache table with -1 (representing unvisited states)
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < 20; i++) {
        cout << dp[i][0] << " ";
    }
    if (solve(1, 0)) cout << "Cycle Exists!";
    else cout << "No Cycle";
    return 0;
}