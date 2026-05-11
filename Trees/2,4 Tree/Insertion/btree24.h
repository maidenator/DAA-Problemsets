#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_BTREE24_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_BTREE24_H

#include "node.hpp"
#include <iostream>
using namespace std;

class BTree24 {
    node* root;

public:
    BTree24() {
        root = nullptr;
    }

    //TODO
    // Helper to properly initialize a node's pointer arrays
    node* create_node(node* par = nullptr) {
        node* n = new node();
        n->parent = par;
        n->size = 0;
        n->children = new node*[5]{nullptr}; // Up to 5 children during overflow
        return n;
    }

    void split(node* curr) {
        // Promote the 3rd key (index 2)
        int promoted_key = curr->keys[2];

        // Create right node for the split
        node* right_node = create_node(curr->parent);
        right_node->keys[0] = curr->keys[3];
        right_node->size = 1;

        // Move the rightmost children to the right node
        right_node->children[0] = curr->children[3];
        if (right_node->children[0]) right_node->children[0]->parent = right_node;

        right_node->children[1] = curr->children[4];
        if (right_node->children[1]) right_node->children[1]->parent = right_node;

        // Left node (curr) keeps the first two keys
        curr->size = 2;
        curr->children[3] = nullptr;
        curr->children[4] = nullptr;

        // If we split the root, create a new root
        if (curr == root) {
            root = create_node();
            root->keys[0] = promoted_key;
            root->size = 1;
            root->children[0] = curr;
            root->children[1] = right_node;
            curr->parent = root;
            right_node->parent = root;
        } else {
            // Push the promoted key up to the parent
            insert_into_node(curr->parent, promoted_key, right_node);
        }
    }

    void insert_into_node(node* curr, int num, node* right_child) {
        int i = curr->size - 1;
        // Shift keys and children to the right to make room
        while (i >= 0 && curr->keys[i] > num) {
            curr->keys[i + 1] = curr->keys[i];
            curr->children[i + 2] = curr->children[i + 1];
            i--;
        }

        curr->keys[i + 1] = num;
        curr->children[i + 2] = right_child;
        if (right_child) right_child->parent = curr;
        curr->size++;

        // Check for (2,4) tree overflow condition (4 keys)
        if (curr->size == 4) {
            split(curr);
        }
    }

    bool insert(int num) {
        if (!root) {
            root = create_node();
            root->keys[0] = num;
            root->size = 1;
            return true;
        }

        node* curr = root;

        // Traverse down to the appropriate leaf
        while (curr->children[0] != nullptr) {
            int i = 0;
            while (i < curr->size && num > curr->keys[i]) {
                i++;
            }

            // Check for duplicate in internal nodes
            if (i < curr->size && curr->keys[i] == num) {
                return false;
            }

            curr = curr->children[i];
        }

        // Check for duplicate in the leaf node before inserting
        for (int i = 0; i < curr->size; i++) {
            if (curr->keys[i] == num) {
                return false;
            }
        }

        insert_into_node(curr, num, nullptr);
        return true;
    }

    // WARNING. Do not modify these methods.
    // Doing so will nullify your score for this activity.
    void print_node(string s, node* n) {
        cout << s << ": ";
        for (int i = 0; i < n->size; i++) {
            cout << n->keys[i] << " ";
        }
        cout << endl;
        for (int i = 0; i <= n->size; i++) {
            if (n->children[i]) {
                print_node("Child " + to_string(i+1) + " of " + s,n->children[i]);
            }
        }
    }
    bool check_parent(node* curr, node* par) {
        if (!curr) {
            return true;
        }
        if (curr->parent != par) {
            if (!curr->parent) {
                cout << "Illegal parent of [" << curr->keys[0] << ",...]: NULL -- must be [" << par->keys[0] << ",...]" << endl;
            } else if (!par) {
                cout << "Illegal parent of [" << curr->keys[0] << ",...]: [" << curr->parent->keys[0] << ",...] -- must be NULL" << endl;
            } else {
                cout << "Illegal parent of [" << curr->keys[0] << ",...]: [" << curr->parent->keys[0] << ",...] -- must be [" << par->keys[0] << ",...]" << endl;
            }
            return false;
        }
        bool res = true;
        for (int i = 0; i < curr->size; i++) {
            res &= check_parent(curr->children[i], curr);
        }
        return res;
    }

    void print() {
        print_node("Root", root);
        check_parent(root, NULL);
    }
};

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_BTREE24_H
