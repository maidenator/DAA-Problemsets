#include <iostream>
#include <string>
using namespace std;


void solve(int set[]) {
    bool mark[4];
    int res = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (set[i] == set[j] && i != j && !mark[j]) {
                res++;
                mark[j] = true;
            }
        }
    }
    if (res != 0 && res != 3) res--;
    cout<<res;
}

int main() {
    int set[4];
    for (int i = 0; i < 4; i++) {
        cin>>set[i];
    }
    solve(set);
}