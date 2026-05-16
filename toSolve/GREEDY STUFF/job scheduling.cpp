#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cout << "Jobs, Machines: "; cin >> n >> m;

    vector<int> jobs(n), machines(m, 0);
    cout << "Enter job times:\n";
    for (int i = 0; i < n; i++) cin >> jobs[i];

    // 1. LPT Step: Sort jobs descending
    sort(jobs.begin(), jobs.end(), greater<int>());

    // 2. Greedy Allocation: Directly find and update the min-loaded machine
    for (int x : jobs) {
        *min_element(machines.begin(), machines.end()) += x;
    }

    // 3. Output Makespan: Find the maximum accumulated load
    cout << "Res: " << *max_element(machines.begin(), machines.end()) << "\n";
    return 0;
}