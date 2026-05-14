#include <iostream>
#include <vector>
using namespace std;

int calculateKnapsack(const vector<int>& items, const vector<int>& weight, int size, int cap) {
    // 1D DP array initialized to 0
    vector<int> dp(cap + 1, 0);

    for (int i = 0; i < size; i++) {
        // Iterate backwards to avoid reusing the same item
        for (int w = cap; w >= weight[i]; w--) {
            int exclude = dp[w];
            int include = items[i] + dp[w - weight[i]];
            dp[w] = max(exclude, include);
        }
    }
    return dp[cap];
}

int main() {
    int size, cap;
    cout << "Enter the number of items: ";
    cin >> size;

    vector<int> items(size), weight(size);
    cout << "Enter the value of the item and its corresponding weight:\n\n";
    for (int i = 0; i < size; i++) {
        cin >> items[i] >> weight[i];
    }

    cout << "Enter the capacity of the knapsack:\n";
    cin >> cap;

    int res = calculateKnapsack(items, weight, size, cap);
    cout << "Res: " << res << "\n";

    return 0;
}