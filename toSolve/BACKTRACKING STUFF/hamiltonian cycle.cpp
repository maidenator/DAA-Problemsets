#include <iostream>
using namespace std;

int n, edges;
int graph[20][20] = {0};
bool found = false;

// No isSafe function needed because logic is inside the loop
void solve(int mask, int pos) {
    if (found) return;

    if (mask == (1 << n) - 1) {
        if (graph[pos][0]) found = true; // Return to start
        return;
    }

    for (int i = 0; i < n; i++) {
        // Check: Edge exists AND not visited
        if (graph[pos][i] && !(mask & (1 << i))) {
            solve(mask | (1 << i), i); // Recurse
            // No backtrack needed for mask because it's passed by value!
        }
    }
}

int main() {
    cout << "N, Edges: "; cin >> n >> edges;
    for (int i = 0, u, v; i < edges; i++) {
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }
    solve(1, 0); // Start at node 0 with mask 1
    if (found) cout << "Cycle Exists!";
    else cout << "No Cycle";
    return 0;
}