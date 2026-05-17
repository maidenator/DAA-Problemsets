#include <iostream>

using namespace std;



int main() {
    cout<<"Enter the size of the array: ";
    int size;
    cin>>size;
    int set[size];

    cout<<"Enter the elements of the array:\n";
    for (int i = 0; i < size; i++) {
        cin>>set[i];
    }

    cout<<"Enter the number to check: ";
    int target;
    cin >> target;

    bool table[size + 1][target + 1];

    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= target; j++) {
            table[i][j] = false;
        }
    }
 
    for (int i = 0; i <= size; i++) {
        table[i][0] = true;
    }

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= target; j++) {
            int currentNum = set[i - 1];
            if (currentNum <= j) {
                table[i][j] = table[i - 1][j] || table[i - 1][j - currentNum];
            } else {
                table[i][j] = table[i - 1][j];
            }
        }
    }
    if (table[size+1][target+1])
        cout<<"There exists a subset";
    else
        cout<<"There is no subset";
}