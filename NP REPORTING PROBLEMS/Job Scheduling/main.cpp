#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int j, m;
    cin >> j >> m;

    int jobs[j], machines[m] = {0};
    for (int i = 0; i < j; i++) cin >> jobs[i];

    sort(jobs, jobs + j, greater<int>());

    for (int i : jobs) {
        *min_element(machines, machines+m) += i;
    }

    cout << "Res: " << *max_element(machines, machines + m);
}