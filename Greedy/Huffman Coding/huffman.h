#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_HUFFMAN_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_HUFFMAN_H

#include "node.h"
node* huffman_code(Heap* heap) {
    while(heap->size() > 1) {
        node* left = heap->removeMin();
        node* right = heap->removeMin();

        node* p = new node('\0', left->weight + right->weight);

        p->left = left;
        p->right = right;

        left->parent = p;
        right->parent = p;

        heap->insert(p);
    }
    return heap->removeMin();
}

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_HUFFMAN_H
