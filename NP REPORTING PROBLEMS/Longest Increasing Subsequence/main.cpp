#include <iostream>
#include <algorithm>
using namespace std;

int dp[1001]; // Global: will overwrite with 1s
int arr[1001];

void solveLIS(int n) {
    if (n == 0) return;

    // 1. Initialize all scores to 1
    for (int i = 0; i < n; i++) dp[i] = 1;

    int maxLIS = 1;
    // 2. Fill Table (Nested Loops)
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        maxLIS = max(maxLIS, dp[i]);
    }

    cout << "LIS Length: " << maxLIS << "\n";
}

int main() {
    int n;
    cout << "Enter size: "; cin >> n;
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    solveLIS(n);
    return 0;
}