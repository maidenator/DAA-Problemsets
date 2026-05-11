#include <iostream>
#include <algorithm>
using namespace std;


int partition(int* arr, int low, int high) {
    int pivot = arr[low];
    int i = low;

    for (int j = low + 1; j <= high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i], arr[low]);
    return i;
}

void quickSort(int* arr, int low, int high) {
    if (low >= high) return;

    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

int* sort(int* arr, int size) {
    quickSort(arr, 0, size - 1);
    return arr;
}

int main() {
    cout<<"[ QUICK SORT ]\n\n\n";

    int size;
    cout<<"ENTER SIZE: ";
    cin>>size;
    int* arr = new int[size];

    cout<<"ENTER ELEMENTS:\n";
    for (int i = 0; i < size; i++) {
        cin>>arr[i];
    }

    arr = sort(arr, size);

    cout<<"SORTED ELEMENTS:\n";
    for (int i = 0; i < size; i++) {
        cout<<arr[i]<<" ";
    }
}