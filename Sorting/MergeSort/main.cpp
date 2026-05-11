#include <iostream>
using namespace std;


void merge(int* arr, int left, int mid, int right) {
    int size = right - left + 1;
    int* temp = new int[size];

    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int k = 0; k < size; k++) {
        arr[left + k] = temp[k];
    }

    delete[] temp;
}

void mergeSort(int* arr, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int* sort(int* arr, int size) {
    mergeSort(arr, 0, size - 1);
    return arr;
}

int main() {
    cout<<"[ MERGE SORT ]\n\n\n";

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