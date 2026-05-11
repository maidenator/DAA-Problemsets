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

    bool search(node* curr, int num) {
        if (num == curr->element)
            return true;

        if (num < curr->element)
            return search(curr->left, num);
        else
            return search(curr->right, num);
    }

    //Returns the node that contains num, or the closest node to it
    node* search_node(node* curr, int num) {
        if (curr->element == num)
            return curr;

        if (num < curr->element) {
            if (curr->left) return search_node(curr->left, num);
            return curr;
        } else {
            if (curr->right) return search_node(curr->right, num);
            return curr;
        }
    }

    void zigleft(node* x) {
        node* y = x->parent;
        node* z = y->parent;

        x->parent = z;
        if (!z) root = x;
        else if (z->left == y) z->left = x;
        else z->right = x;

        y->right = x->left;
        if (x->left) x->left->parent = y;

        x->left = y;
        y->parent = x;
    }

    void zigright(node* x) {
        node* y = x->parent;
        node* z = y->parent;

        x->parent = z;
        if (!z) root = x;
        else if (z->left == y) z->left = x;
        else z->right = x;

        y->left = x->right;
        if (x->right) x->right->parent = y;

        x->right = y;
        y->parent = x;
    }

    node* uncleOf(node* n) {
        if (!n || !n->parent || !n->parent->parent)
            return nullptr;

        node* p = n->parent;
        node* gp = p->parent;

        if (gp->left == p)
            return gp->right;
        else
            return gp->left;
    }

    bool isRed(node* n) {
        return n && n->is_red;
    }

public:
    BSTree() {
        root = nullptr;
        size = 0;
    }

    bool search(int num) {
        return search(root, num);
    }

    bool insert(int num) {
        //Check if !root
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
        if (num < parent->element) parent->left = newNode;
        else parent->right = newNode;
        size++;

        //3. Check for violations
        while (newNode != root && newNode->is_red && parent->is_red) {
            node* uncle = uncleOf(newNode);
            if (uncle == nullptr || !uncle->is_red) {
                cout<<"UNCLE IS BLACK (RESTRUCTURE & RECOLOR)\n";
                node* newParent = restructure(newNode);
                newParent->is_red = false;
                if (newParent->left) newParent->left->is_red = true;
                if (newParent->right) newParent->right->is_red = true;
                break;
            }

            if (uncle->is_red) {
                cout<<"UNCLE IS RED (RECOLOR)\n";
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
            bool is_left = curr->parent->left == curr;
            node* sibling = is_left ? curr->parent->right : curr->parent->left;

            // Case 3: Sibling is Red
            if (isRed(sibling)) {
                cout<<"SIBLING IS RED\n";
                curr->parent->is_red = true;
                sibling->is_red = false;
                restructure(sibling);
                sibling = is_left ? curr->parent->right : curr->parent->left;
            }

            // Case 2: Sibling is Black, and both its children are Black
            if (!isRed(sibling->left) && !isRed(sibling->right)) {
                cout<<"SIBLING IS BLACK & BLACK CHILDREN: PUSHING UP THE BLACKNESS\n";
                sibling->is_red = true;
                curr = curr->parent;
            }

            // Case 1: Sibling is Black, at least one child is Red
            else {
                cout<<"SIBLING IS BLACK & 1 CHILD\n";
                node* far_child = is_left ? sibling->right : sibling->left;
                node* near_child = is_left ? sibling->left : sibling->right;

                // Subcase: Near child is Red, Far child is Black
                if (isRed(near_child) && !isRed(far_child)) {
                    cout<<"NEAR CHILD IS RED\n";
                    near_child->is_red = false;
                    sibling->is_red = true;
                    restructure(near_child);
                    sibling = is_left ? curr->parent->right : curr->parent->left;
                    far_child = is_left ? sibling->right : sibling->left;
                }

                //Subcase: Far child is Red
                cout<<"FAR CHILD IS RED\n";
                sibling->is_red = curr->parent->is_red;
                curr->parent->is_red = false;
                if (far_child) far_child->is_red = false;
                restructure(sibling);
                curr = root; // Done
            }
        }
        if (curr) curr->is_red = false;
    }

    node* restructure(node* n) {
        node* p = n->parent;

        bool ptoc_right = false;
        if (p->right == n)
            ptoc_right = true;

        node* gp = p->parent;

        bool gtop_right = false;
        if (gp != nullptr && gp->right == p)
            gtop_right = true;

        // gp
        //  \
        //   p
        //    \
        //     n
        if (gp && gtop_right && ptoc_right) {
            cout<<"ZIGLEFT ON NODE "<<n->element<<"\n";
            zigleft(p);
            return p;
        }
        //  gp
        //    \
        //     p
        //    /
        //   n
        if (gp && gtop_right) {
            cout<<"ZIGZAGLEFT ON NODE "<<n->element<<"\n";
            zigright(n);
            zigleft(n);
            return n;
        }
        //     gp
        //    /
        //   p
        //  /
        // n
        if (gp && !ptoc_right) {
            cout<<"ZIGRIGHT ON NODE "<<n->element<<"\n";
            zigright(p);
            return p;
        }
        //    gp
        //   /
        //  p
        //   \
        //    n
        if (gp) {
            cout<<"ZIGZAGRIGHT ON NODE "<<n->element<<"\n";
            zigleft(n);
            zigright(n);
            return n;
        }
        //  p
        //   \
        //    n
        if (ptoc_right) {
            cout<<"ZIGLEFT ON NODE "<<n->element<<"\n";
            zigleft(n);
            return n;
        }
        //   p
        //  /
        // n
        else {
            cout<<"ZIGRIGHT ON NODE "<<n->element<<"\n";
            zigright(n);
            return n;
        }
    }

    bool remove(int num) {
        if (isEmpty()) {
            return false;
        }
        node* rem_node = search_node(root, num);
        if (rem_node->element != num) {
            return false;
        }

        // FIND the number of children.
        int children = 0;
        // 0-1 Tabulation - no children
        // -1 - left child only
        // 1 - right child only
        // 2 - both children
        if (rem_node->right) {
            children = 1;
        }
        if (rem_node->left) {
            if (children == 1) {
                children = 2;
            } else {
                children = -1;
            }
        }

        if (children == 0) { // NO CHILDREN
            node* parent = rem_node->parent;

            if(!rem_node->is_red){
                deleteFix(rem_node);
            }

            if (!parent) {
                root = NULL;
            } else {
                if (rem_node == parent->left) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
            }

            free(rem_node);
            size--;
        } else if (children == -1 || children == 1) { // ONE CHILD
            node* parent = rem_node->parent;
            node* child;
            if (children == -1) {
                child = rem_node->left;
            } else {
                child = rem_node->right;
            }

            child->parent = parent;

            if (!parent) {
                root = child;
            } else {
                if (parent->left == rem_node) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
            }

            deleteFix(child);

            free(rem_node);
            size--;
        } else { // TWO CHILDREN
            node* restructureNode = rem_node;

            node* right_st = rem_node->right;
            while (right_st->left != NULL) {
                right_st = right_st->left;
            }

            if(right_st != rem_node->right)
                restructureNode = right_st;

            if(!restructureNode->is_red)
                deleteFix(restructureNode);

            int temp = right_st->element;
            remove(temp);
            rem_node->element = temp;
        }

        return true;
    }

    //BUILT IN FUNCTIONS
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
