#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int dp[1001][1001]; // Global: already initialized to 0

void solveLCS(string s1, string s2) {
    int m = s1.size(), n = s2.size();

    // 1. Fill Table
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = s1[i-1] == s2[j-1] ? 1 + dp[i-1][j-1] : max(dp[i-1][j], dp[i][j-1]);

    // 2. Backtrack for String (Optional but common)
    string res = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            res += s1[i-1]; i--; j--;
        }
        else dp[i-1][j] > dp[i][j-1] ? i-- : j--;
    }
    reverse(res.begin(), res.end());

    cout << "Length: " << dp[m][n];
    cout << "String: " << res << "\n";
}

int main() {
    string s1, s2;
    cout << "Enter strings: "; cin >> s1 >> s2;
    solveLCS(s1, s2);
    return 0;
}