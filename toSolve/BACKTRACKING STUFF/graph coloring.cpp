#include <iostream>
using namespace std;

int n, m, edges;
int graph[20][20] = {0};
int colors[20] = {0}; // colors[node] = color_index

bool isSafe(int v, int c) {
    for (int i = 0; i < n; i++) {
        // Check if neighbor has the same color
        if (graph[v][i] && colors[i] == c)
            return false;
    }
    return true;
}

bool solve(int v) {
    if (v == n) return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            colors[v] = c;    // Paint
            if (solve(v + 1)) return true;
            colors[v] = 0;    // Backtrack
        }
    }
    return false;
}

int main() {
    cout << "N, M, Edges: "; cin >> n >> m >> edges;
    for (int i = 0, u, v; i < edges; i++) {
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }
    if (solve(0)) {
        for (int i = 0; i < n; i++) cout << colors[i] << " ";
    } else cout << "No Solution";
    return 0;
}