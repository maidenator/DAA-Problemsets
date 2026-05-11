#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
    int value;
    int weight;
    float ratio;
};

double calculateKnapsack(int * values, int * weight, int size, int cap) {
    if (size == 0 || cap == 0) return -1;

    Item* items = new Item[size];
    for (int i = 0; i < size; i++) {
        items[i].value = values[i];
        items[i].weight = weight[i];
        items[i].ratio = (float)values[i] / (float)weight[i];
    }

    //std sort abuse
    sort(items, items + size, [](Item a, Item b) {return a.ratio > b.ratio;});

    double totalValue = 0;
    int currentWeight = 0;

    for (int i = 0; i < size; i++) {
        if (currentWeight + items[i].weight <= cap) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            int remaining = cap - currentWeight;
            totalValue += items[i].value * ((double)remaining / items[i].weight);
            break;
        }
    }
    return totalValue;
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
    double res = calculateKnapsack(items, weight, size, cap);
    cout << "Res: " << res;
}