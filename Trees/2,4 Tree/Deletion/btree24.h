#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_BTREE24_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_BTREE24_H

#include "node.hpp"
#include <iostream>
using namespace std;

class BTree24 {
	public:
	node* root;

	BTree24() {
		root = nullptr;
	}

	virtual bool insert(int num) = 0;
	virtual node* search(int, node*) = 0;
	virtual void print() = 0;

    // Helper 1: Find the index of the current node inside its parent's children array
    int get_index_in_parent(node* n) {
        if (!n->parent) return -1;
        for (int i = 0; i <= n->parent->size; i++) {
            if (n->parent->children[i] == n) return i;
        }
        return -1;
    }

    // Helper 2: Handle node underflow using the Size-Based Tie-Breaker logic
    void handle_underflow(node* curr) {
        if (curr == root) {
            if (curr->size == 0 && curr->children[0] != nullptr) {
                root = curr->children[0];
                root->parent = nullptr;
            }
            return;
        }

        node* parent = curr->parent;
        int idx = get_index_in_parent(curr);

        node* left_sib = (idx > 0) ? parent->children[idx - 1] : nullptr;
        node* right_sib = (idx < parent->size) ? parent->children[idx + 1] : nullptr;

        int left_size = left_sib ? left_sib->size : 0;
        int right_size = right_sib ? right_sib->size : 0;

        // Strategy 1: Transfer from the sibling with the most keys.
        // If they have the same amount of keys, prioritize the RIGHT sibling.
        if (right_size > 1 && right_size >= left_size) {
            // Transfer from Right
            curr->keys[curr->size] = parent->keys[idx];
            parent->keys[idx] = right_sib->keys[0];
            curr->children[curr->size + 1] = right_sib->children[0];
            if (curr->children[curr->size + 1]) curr->children[curr->size + 1]->parent = curr;

            for (int i = 0; i < right_sib->size - 1; i++) right_sib->keys[i] = right_sib->keys[i + 1];
            for (int i = 0; i < right_sib->size; i++) right_sib->children[i] = right_sib->children[i + 1];

            right_sib->children[right_sib->size] = nullptr;
            right_sib->size--;
            curr->size++;
            return;
        }
        else if (left_size > 1) {
            // Transfer from Left
            for (int i = curr->size; i > 0; i--) curr->keys[i] = curr->keys[i - 1];
            for (int i = curr->size + 1; i > 0; i--) curr->children[i] = curr->children[i - 1];

            curr->keys[0] = parent->keys[idx - 1];
            parent->keys[idx - 1] = left_sib->keys[left_sib->size - 1];
            curr->children[0] = left_sib->children[left_sib->size];
            if (curr->children[0]) curr->children[0]->parent = curr;

            left_sib->children[left_sib->size] = nullptr;
            left_sib->size--;
            curr->size++;
            return;
        }

        // Strategy 2: Fuse. Prioritize Right sibling first, then Left.
        if (right_sib) {
            // Fuse with Right
            curr->keys[curr->size] = parent->keys[idx];
            for (int i = 0; i < right_sib->size; i++) {
                curr->keys[curr->size + 1 + i] = right_sib->keys[i];
            }
            for (int i = 0; i <= right_sib->size; i++) {
                curr->children[curr->size + 1 + i] = right_sib->children[i];
                if (curr->children[curr->size + 1 + i]) {
                    curr->children[curr->size + 1 + i]->parent = curr;
                }
            }
            curr->size += right_sib->size + 1;

            for (int i = idx; i < parent->size - 1; i++) parent->keys[i] = parent->keys[i + 1];
            for (int i = idx + 1; i < parent->size; i++) parent->children[i] = parent->children[i + 1];

            parent->children[parent->size] = nullptr;
            parent->size--;
            if (parent->size == 0) handle_underflow(parent);
            return;
        }
        else if (left_sib) {
            // Fuse with Left
            left_sib->keys[left_sib->size] = parent->keys[idx - 1];
            for (int i = 0; i < curr->size; i++) {
                left_sib->keys[left_sib->size + 1 + i] = curr->keys[i];
            }
            for (int i = 0; i <= curr->size; i++) {
                left_sib->children[left_sib->size + 1 + i] = curr->children[i];
                if (left_sib->children[left_sib->size + 1 + i]) {
                    left_sib->children[left_sib->size + 1 + i]->parent = left_sib;
                }
            }
            left_sib->size += curr->size + 1;

            for (int i = idx - 1; i < parent->size - 1; i++) parent->keys[i] = parent->keys[i + 1];
            for (int i = idx; i < parent->size; i++) parent->children[i] = parent->children[i + 1];

            parent->children[parent->size] = nullptr;
            parent->size--;
            if (parent->size == 0) handle_underflow(parent);
            return;
        }
    }

    // Helper 3: Remove key directly and trigger underflow if empty
    void remove_from_node(node* curr, int index) {
        for (int i = index; i < curr->size - 1; i++) {
            curr->keys[i] = curr->keys[i + 1];
        }
        curr->size--;

        if (curr->size == 0) {
            handle_underflow(curr);
        }
    }

    // Main Remove Function
    bool remove(int num) {
        node* curr = root;
        while (curr) {
            int i = 0;
            while (i < curr->size && num > curr->keys[i]) i++;

            if (i < curr->size && curr->keys[i] == num) {
                if (curr->children[0] == nullptr) {
                    // Case 1: Key is in a leaf node
                    remove_from_node(curr, i);

                    if (root && root->size == 0 && root->children[0] == nullptr) {
                        root = nullptr;
                    }
                } else {
                    // Case 2: Key is in an internal node.
                    // Replace with the INORDER SUCCESSOR (smallest key in the right subtree)
                    node* succ = curr->children[i + 1];
                    while (succ->children[0] != nullptr) {
                        succ = succ->children[0];
                    }

                    curr->keys[i] = succ->keys[0];
                    remove_from_node(succ, 0);
                }
                return true;
            }
            else if (curr->children[0] == nullptr) {
                return false;
            }
            else {
                curr = curr->children[i];
            }
        }

        return false;
    }
};

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_BTREE24_H
