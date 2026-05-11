#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int** graph;
int n;
int min_cost = INT_MAX;

void solve(int mask, int pos, int cost) {
    if(cost >= min_cost) return;
    
    if(mask == (1 << n) - 1) {
        int final_path = cost + graph[pos][0];
        if(final_path < min_cost) 
            min_cost = final_path;
        
        return;
    }
    
    for(int i = 0; i < n; i++) {
        if(!(mask & (1 << i))) 
            solve(mask | (1 << i), i, cost + graph[pos][i]);
    }
}

int main() {
    cout<<"Enter number of cities: ";
    cin>>n;
    
    graph = new int*[n];
    cout<<"Enter adjacency matrix:\n";
    
    for(int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for(int j = 0; j < n; j++) {
            cin>>graph[i][j];
        }
    }
    
    solve(1, 0, 0);
    cout<<"Minimum cost: "<<min_cost;
}