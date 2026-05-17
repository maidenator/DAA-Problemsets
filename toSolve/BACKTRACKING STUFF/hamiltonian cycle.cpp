#include <iostream>
using namespace std;

int n, edges;
int graph[20][20] = {0};
bool visited[20] = {false};

bool solve(int pos, int count) {
    // Base Case: If we have visited all 'n' nodes
    if (count == n) {
        // Check if there is an edge back to the starting node (0)
        return graph[pos][0];
    }
    // Try going to every other node
    for (int i = 0; i < n; i++) {
        // If there is an edge AND the node 'i' hasn't been visited yet
        if (graph[pos][i] && !visited[i]) {
            // 1. CHOOSE: Mark the node as visited
            visited[i] = true;
            // 2. EXPLORE: Recurse to the next node and increment our visited count
            if (solve(i, count + 1)) {
                return true; // We found a valid cycle! Pass it up the chain.
            }
            // 3. UN-CHOOSE (Backtrack): If that path failed, un-mark it so other paths can try using it
            visited[i] = false;
        }
    }
    // If we tried all neighbors and none worked, return false
    return false;
}

int main() {
    cout << "N, Edges: ";
    cin >> n >> edges;
    for (int i = 0, u, v; i < edges; i++) {
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }

    // Setup the starting conditions for node 0
    visited[0] = true;

    // Start at node 0, with a visited count of 1
    if (solve(0, 1)) {
        cout << "Cycle Exists!";
    } else {
        cout << "No Cycle";
    }
    return 0;
}