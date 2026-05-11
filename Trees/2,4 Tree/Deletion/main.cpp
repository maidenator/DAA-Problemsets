#include "hidden.hpp"
#include <iostream>
using namespace std;
int main() {
    BTree24* tree = new MyBTree();

    char op;
    int num;
    bool res;
    do {
        cout << "Operation: ";
        cin >> op;
        switch (op) {
            case 'i':
                cin >> num;
                tree->insert(num);
                break;
            case 'r':
                cin >> num;
                res = tree->remove(num);
                if (res) {
                    cout << "Removed " << num << endl;
                } else {
                    cout << num << " not found" << endl;
                }
                break;
            case 'p':
                tree->print();
                break;
            case 'x':
                cout << "Exiting";
                break;
            default:
                cout << "Invalid operation";
        }
    } while (op != 'x');
    return 0;
};