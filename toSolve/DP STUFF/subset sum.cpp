#include <iostream>
using namespace std;

bool dp_ss[10001];
int nums[1001];

void solveSubsetSum(int n, int target) {
    // 1. Base case: sum 0 is always possible
    dp_ss[0] = true;

    // 2. Fill Table (Nested Loops)
    for (int i = 0; i < n; i++) {
        int x = nums[i];
        // BACKWARD loop is the key for 1D Subset Sum/Knapsack
        for (int j = target; j >= x; j--) {
            if (dp_ss[j - x])
                dp_ss[j] = true;
        }
    }

    if (dp_ss[target]) cout << "Subset Found!\n";
    else cout << "No Subset\n";
}

int main() {
    int n, target;
    cout << "Size, Target: "; cin >> n >> target;
    for (int i = 0; i < n; i++) cin >> nums[i];
    solveSubsetSum(n, target);
    return 0;
}