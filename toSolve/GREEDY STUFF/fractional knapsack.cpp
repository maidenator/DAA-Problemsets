#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double calculateKnapsack(const vector<int>& values, const vector<int>& weight, int size, int cap) {
    if (size == 0 || cap == 0) return 0;

    // 1. Create index array [0, 1, 2... size-1]
    vector<int> idx(size);
    for (int i = 0; i < size; i++) idx[i] = i;

    // 2. Sort indices by Value/Weight Ratio
    sort(idx.begin(), idx.end(), [&](int a, int b){ return values[a] * weight[b] > values[b] * weight[a]; });
    double totalValue = 0;

    // 3. Greedy Process
    for (int i : idx) {
        if (weight[i] <= cap) {
            cap -= weight[i];
            totalValue += values[i];
        } else {
            totalValue += values[i] * ((double)cap / weight[i]);
            break;
        }
    }
    return totalValue;
}

int main() {
    int size, cap;
    cout << "Enter the number of items: "; cin >> size;

    vector<int> values(size), weight(size);
    cout << "Enter the value of the item and its corresponding weight:\n";
    for (int i = 0; i < size; i++) cin >> values[i] >> weight[i];

    cout << "Enter the capacity of the knapsack: "; cin >> cap;

    double res = calculateKnapsack(values, weight, size, cap);
    cout << "Res: " << res << "\n";
    return 0;
}