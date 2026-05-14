#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double calculateKnapsack(const vector<int>& values, const vector<int>& weight, int size, int cap) {
    if (size == 0 || cap == 0) return 0;

    // Create an array of indices [0, 1, 2... size-1]
    vector<int> idx(size);
    for (int i = 0; i < size; i++) idx[i] = i;

    // std::sort abuse: Sort the indices based on the value/weight ratio
    sort(idx.begin(), idx.end(), [&](int a, int b) {return (double)values[a] / weight[a] > (double)values[b] / weight[b];});

    double totalValue = 0;

    // Iterate through our sorted indices
    for (int i : idx) {
        if (weight[i] <= cap) {
            cap -= weight[i];
            totalValue += values[i];
        } else {
            // Take the fractional remainder and break
            totalValue += values[i] * ((double)cap / weight[i]);
            break;
        }
    }
    return totalValue;
}

int main() {
    int size, cap;
    cout << "Enter the number of items: ";
    cin >> size;

    // Using vectors prevents the memory leak from 'new int[]'
    vector<int> values(size), weight(size);
    cout << "Enter the value of the item and its corresponding weight:\n\n";
    for (int i = 0; i < size; i++) {
        cin >> values[i] >> weight[i];
    }

    cout << "Enter the capacity of the knapsack:\n";
    cin >> cap;

    double res = calculateKnapsack(values, weight, size, cap);
    cout << "Res: " << res << "\n";

    return 0;
}