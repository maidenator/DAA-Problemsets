#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_HEAP_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_HEAP_H
#include "node.h"

class Heap {
    int left(int i) { return (2 * i) + 1; }
    int right(int i) { return (2 * i) + 2; }
    int parent(int i) { return (i - 1) / 2; }

    public:
    int Size;
    int cap;
    node** arr;

    Heap() {
        Size = 0;
        cap = 30;
        arr = new node*[cap];
    }
    // TODO insert
    void insert(node* n) {
        arr[Size] = n;
        int index = Size;
        Size++;

        while(index > 0 && arr[index]->weight < arr[parent(index)]->weight) {
            int pIndex = parent(index);
            swap(arr[index], arr[pIndex]);
            index = pIndex;
        }
    }

    // TODO removeMin
    node* removeMin() {
        if(Size == 0) return nullptr;
        node* removed = arr[0];

        arr[0] = arr[Size-1];
        Size--;

        int index = 0;
        while(left(index) < Size) {
            int smallest = left(index);
            int r = right(index);

            if(r < Size && arr[r]->weight < arr[smallest]->weight)
                smallest = r;

            if(arr[index]->weight < arr[smallest]->weight)
                break;

            swap(arr[index], arr[smallest]);
            index = smallest;
        }
        return removed;
    }

    // TODO size
    int size() {
        return Size;
    }
};

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_HEAP_H
