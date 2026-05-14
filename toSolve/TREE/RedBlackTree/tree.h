#ifndef TREES_TREE_H
#define TREES_TREE_H

#include "node.h"
#include <iostream>
using namespace std;
class BSTree {
    node* root;
    int size;

    //UTILITIES:
    node* create_node(int num, node* parent) {
        node* n = (node*)malloc(sizeof(node));
        n->element = num;
        n->parent = parent;
        n->is_red = true;
        n->left = n->right = nullptr;
        return n;
    }

    //Returns the node that contains num, or the node closest to it
    node* search_node(node* curr, int num) {
        if (curr->element == num) return curr;
        node* next = (num < curr->element) ? curr->left : curr->right;
        return next ? search_node(next, num) : curr;
    }

    //Replaces a node x with y
    void transplant(node* x, node* y) {
        if (!x->parent)
            root = y;
        else x->parent->left == x? x->parent->left : x->parent->right = y;

        if (y)
            y->parent = x->parent;
    }

    void zigleft(node* x) {
        node* y = x->parent;

        transplant(x, y);

        y->right = x->left;
        if (x->left) x->left->parent = y;

        x->left = y;
        y->parent = x;
    }

    void zigright(node* x) {
        node* y = x->parent;

        transplant(x, y);

        y->left = x->right;
        if (x->right) x->right->parent = y;

        x->right = y;
        y->parent = x;
    }

    node* uncleOf(node* n) {
        if (!n || !n->parent || !n->parent->parent)
            return nullptr;
        node* gp = n->parent->parent;
        return gp->left == n->parent ? gp->right : gp->left;
    }

    bool isRed(node* n) {
        //Make sure n exists THEN check if red
        return n && n->is_red;
    }

public:
    BSTree() {
        root = nullptr;
        size = 0;
    }

    bool search(int num) {
        return search_node(root, num)->element == num;
    }

    bool insert(int num) {
        //0. Check if !root
        if (!root) {
            root = create_node(num, nullptr);
            root->is_red = false;
            size++;
            return true;
        }

        //1. Do not insert of node exists
        if (search_node(root, num)->element == num) return false;

        //2. Insert to its rightful place
        node* parent = search_node(root, num);
        node* newNode = create_node(num, parent);
        (num < parent->element ? parent->left : parent->right) = newNode;
        size++;

        //3. Check for violations
        while (newNode != root && newNode->is_red && parent->is_red) {
            node* uncle = uncleOf(newNode);
            //UNC IS BLACK
            if (uncle == nullptr || !uncle->is_red) {
                cout << "UNCLE IS BLACK (RESTRUCTURE & RECOLOR)\n";
                node* newParent = restructure(newNode, true);
                newParent->is_red = false;
                if (newParent->left) newParent->left->is_red = true;
                if (newParent->right) newParent->right->is_red = true;
                break;
            }
            //UNC IS RED
            if (uncle->is_red) {
                cout << "UNCLE IS RED (RECOLOR)\n";
                uncle->is_red = false;
                parent->is_red = false;
                parent->parent->is_red = true;
                newNode = parent->parent;
                parent  = newNode->parent;
            }
        }
        root->is_red = false;
        return true;
    }

    void deleteFix(node* n) {
    node* curr = n;

    while (curr != root && !isRed(curr)) {
        node* p = curr->parent;
        bool is_left = (curr == p->left);

        // 1. DYNAMIC ASSIGNMENT: Identify sibling based on our position
        node* sibling = is_left ? p->right : p->left;

        // CASE 3: Sibling is Red
        if (isRed(sibling)) {
            cout << "DELETION Violation: Case 3\n";
            p->is_red = true;
            sibling->is_red = false;
            restructure(sibling, false);
            // The rotation changed the tree, so we MUST update the sibling pointer
            sibling = is_left ? p->right : p->left;
        }

        // 2. DYNAMIC NEPHEWS: Identify nephews based on our position
        node* near_child = is_left ? sibling->left : sibling->right;
        node* far_child = is_left ? sibling->right : sibling->left;

        // CASE 2: Sibling is Black, Both Nephews are Black
        if (!isRed(near_child) && !isRed(far_child)) {
            cout << "DELETION Violation: Case 2\n";
            sibling->is_red = true;
            curr = p; // Push the double-black status up to the parent
        }

        // CASE 1: Sibling is Black, At least one Nephew is Red
        else {
            cout << "DELETION Violation: Case 1\n";

            // Subcase: Near Nephew is Red, Far is Black (The "Kink")
            if (!isRed(far_child)) {
                near_child->is_red = false;
                sibling->is_red = true;
                restructure(near_child, true); // Straighten the kink

                // Update pointers after straightening
                sibling = is_left ? p->right : p->left;
                far_child = is_left ? sibling->right : sibling->left;
            }

            // Subcase: Far Nephew is Red (The "Line")
            sibling->is_red = p->is_red;     // Sibling takes parent's color
            p->is_red = false;               // Parent becomes Black
            if (far_child) far_child->is_red = false; // Far Nephew becomes Black

            restructure(sibling, true); // The final balancing rotation
            curr = root; // Force the loop to terminate
        }
    }

    // Ensure the final node (or root) is Black
    if (curr) curr->is_red = false;
}

    node* restructure(node* child, bool print) {
        node* par = child->parent;
        node* gp = par->parent;

        bool PR = (par->right == child);
        bool GR = (gp != nullptr && gp->right == par);

        // NO GP
        if (!gp) {
            if (print) cout << (PR ? "ZIGLEFT\n" : "ZIGRIGHT\n");
            PR ? zigleft(child) : zigright(child);
            return child;
        }

        if (GR && PR) {          // RR
            if (print) cout << "ZIGLEFT\n";
            zigleft(par);
            return par;

        } else if (!GR && !PR) { // LL
            if (print) cout << "ZIGRIGHT\n";
            zigright(par);
            return par;

        } else if (GR && !PR) {  // RL
            if (print) cout << "ZIGZAGLEFT\n";
            zigright(child);
            zigleft(child);
            return child;

        } else {                 // LR
            if (print) cout << "ZIGZAGRIGHT\n";
            zigleft(child);
            zigright(child);
            return child;
        }
    }

    bool remove(int num) {
        node* rem = search_node(root, num);
        if (!rem || rem->element != num) return false; // Not found

        // 1. REDUCE: If two children, swap with successor and target successor for deletion
        if (rem->left && rem->right) {
            node* succ = rem->right;
            while (succ->left) succ = succ->left;
            rem->element = succ->element;
            rem = succ; //WE ARE DELETING THE LEAF NODE NOW
        }

        // 2. SETUP: Identify the only child (or NULL) and remember the color
        node* child = (rem->left) ? rem->left : rem->right;
        bool was_black = !rem->is_red;

        // 3. UNLINK: Let your helper function do the heavy lifting
        transplant(rem, child);

        // 4. FIX: If we removed a Black node, trigger the rebalancing
        if (was_black) {
            // If child exists, fix from child, else, use rem to find parent.
            deleteFix(child ? child : rem);
        }

        // 5. DESTROY
        free(rem);
        size--;
        return true;
    }

    //DO NOT TOUCH
    void print() {
        if (isEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        cout << "PRE-ORDER: ";
        print_preorder(root);
        cout << endl << "IN-ORDER: ";
        print_inorder(root);
        cout << endl << "POST-ORDER: ";
        print_postorder(root);
        cout << endl << "STATUS: " << check_health(root, NULL) << endl;
    }

    bool isEmpty() {
        return size == 0;
    }

    void print_preorder(node* curr) {
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
        if (curr->left != NULL) {
            print_preorder(curr->left);
        }
        if (curr->right != NULL) {
            print_preorder(curr->right);
        }
    }

    void print_inorder(node* curr) {
        if (curr->left != NULL) {
            print_inorder(curr->left);
        }
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
        if (curr->right != NULL) {
            print_inorder(curr->right);
        }
    }

    void print_postorder(node* curr) {
        if (curr->left != NULL) {
            print_postorder(curr->left);
        }
        if (curr->right != NULL) {
            print_postorder(curr->right);
        }
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
    }

    bool check_health(node* curr, node* parent) {
        bool health = curr->parent == parent;
        if (curr->left != NULL) {
            health &= check_health(curr->left, curr);
        }
        if (curr->right != NULL) {
            health &= check_health(curr->right, curr);
        }
        return health;
    }
};

#endif //TREES_TREE_H
