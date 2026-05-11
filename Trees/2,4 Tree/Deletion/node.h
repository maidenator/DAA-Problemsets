#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H

#pragma once
struct node {
    node* parent;
    int keys[5]; // Padded to safely handle overflow
    node** children;
    int size;

    node() {
        parent = nullptr;
        size = 0;
        children = new node*[6]; // Padded to handle overflow
        for(int i = 0; i < 6; i++) {
            children[i] = nullptr;
        }
    }

    bool contains(int num) {
        for (int i = 0; i < size; i++) {
            if (keys[i] == num) {
                return true;
            }
        }
        return false;
    }

    void insertKeyAt(int num, int index) {
        // ONLY shift keys. hidden.hpp handles children array shifting.
        for (int i = size - 1; i >= index; i--) {
            keys[i + 1] = keys[i];
        }

        keys[index] = num;
        size++;
    }
};

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H
