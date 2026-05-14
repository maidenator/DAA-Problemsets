#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double calculateJobScheduling(const vector<int>& profits, const vector<int>& deadlines, int size, int cap) {
    if (size == 0 || cap == 0) return 0;

    // 1. Create index array [0, 1, 2... size-1]
    vector<int> idx(size);
    for (int i = 0; i < size; i++) idx[i] = i;

    // 2. Sort indices by Profit descending
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return profits[a] > profits[b];
    });

    // Use 'cap' as the number of available time slots
    vector<bool> slots(cap, false);
    double totalProfit = 0;

    // 3. Greedy Process (Backfill)
    for (int i : idx) {
        // Try to place job in latest possible slot (from deadline back to 0)
        for (int j = min(cap, deadlines[i]) - 1; j >= 0; j--) {
            if (!slots[j]) {
                slots[j] = true;
                totalProfit += profits[i];
                break;
            }
        }
    }
    return totalProfit;
}

int main() {
    int size, cap;
    cout << "Enter the number of items: "; cin >> size;

    // Twinning variables: values -> profits, weight -> deadlines
    vector<int> values(size), weight(size);
    cout << "Enter the profit of the job and its corresponding deadline:\n";
    for (int i = 0; i < size; i++) cin >> values[i] >> weight[i];

    // For Scheduling, cap is usually the max time or size
    cout << "Enter the maximum time slots available: "; cin >> cap;

    double res = calculateJobScheduling(values, weight, size, cap);
    cout << "Res: " << res << "\n";
    return 0;
}