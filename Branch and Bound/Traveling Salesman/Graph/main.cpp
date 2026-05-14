int getMinOutgoing(int** graph, int n, int city) {
    int minCost = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (i != city && graph[city][i] < minCost) {
            minCost = graph[city][i];
        }
    }
    return minCost;
}

int calculateLowerBound(int** graph, int n, bool* visited, int currCost) {
    int bound = currCost;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            bound += getMinOutgoing(graph, n, i);
        }
    }
    return bound;
}

void solveTSP(int** graph, int n, int currCity, int visitedCtr, int currCost, bool* visited, int& minCost) {
    if (visitedCtr == n) {
        int finalCost = currCost + graph[currCity][0];
        if (finalCost < minCost) {
            minCost = finalCost;
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int nextCost = currCost + graph[currCity][i];
            visited[i] = true;

            int bound = calculateLowerBound(graph, n, visited, nextCost);

            if (bound < minCost) {
                solveTSP(graph, n, i, visitedCtr + 1, nextCost, visited, minCost);
            }

            visited[i] = false;
        }
    }
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter adjacency matrix:" << endl;
    int** graph = new int*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    bool* visited = new bool[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    int minCost = INT_MAX;
    visited[0] = true;

    solveTSP(graph, n, 0, 1, 0, visited, minCost);

    cout << "Minimum cost: " << minCost << endl;

    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] visited;

    return 0;
}