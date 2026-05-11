#include <iostream>
#include <algorithm>
using namespace std;

int calculateKnapsack(const int * items, const int * weight, const int size, int cap) {
    int dp[size + 1][cap + 1];

    for (int i = 0; i <= size; i++)  dp[i][0] = 0;
    for (int w = 0; w <= cap; w++)   dp[0][w] = 0;

    for (int i = 1; i <= size; i++) {
        for (int w = 1; w <= cap; w++) {
            if (weight[i - 1] > w) {
                dp[i][w] = dp[i-1][w];
            } else {
                int exclude = dp[i-1][w];
                int include = items[i-1] + dp[i - 1][w - weight[i - 1]];
                dp[i][w] = max(exclude, include);
            }
        }
    }
    return dp[size][cap];
}
int main() {
    int size;
    cout << "Enter the number of items:";
    cin >> size;
    int* items = new int[size];
    int* weight = new int[size];
    cout << "Enter the value of the item and its corresponding weight:\n\n";
    for (int i = 0; i < size; i++) {
        cin >> items[i] >> weight[i];
    }
    int cap;
    cout << "Enter the capacity of the knapsack:\n";
    cin >> cap;
    int res = calculateKnapsack(items, weight, size, cap);
    cout << "Res: " << res;
}
