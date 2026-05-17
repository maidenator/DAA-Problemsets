    #ifndef TREES_TREE_H
    #define TREES_TREE_H

    #include "node.h"
    #include <iostream>
    using namespace std;
    class BSTree {
        node* root = nullptr;
        int size = 0;

        node* create_node(int num, node* parent) {
            node* n = (node*)malloc(sizeof(node));
            n->element = num;
            n->parent = parent;
            n->is_red = true;
            n->left = n->right = nullptr;
            return n;
        }

        node* search_node(int num, node* curr) {
            if (curr->element == num) return curr;
            node* next = (num < curr->element) ? curr->left : curr->right;
            return next ? search_node(num, next) : curr;
        }

        void transplant(node* oldNode, node* newNode) {
            if (!oldNode->parent)
                root = newNode;
            else if (oldNode->parent->left == oldNode) oldNode->parent->left = newNode;
            else oldNode->parent->right = newNode;

            if (newNode)
                newNode->parent = oldNode->parent;
        }

        void zigleft(node* x) {
            node* y = x->parent;

            transplant(y, x);

            y->right = x->left;
            if (x->left) x->left->parent = y;

            x->left = y;
            y->parent = x;
        }

        void zigright(node* x) {
            node* y = x->parent;

            transplant(y, x);

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

        node* restructure(node* child, bool print) {
            node* par = child->parent;
            node* gp = par->parent;

            bool PR = (par->right == child);
            bool GR = (gp != nullptr && gp->right == par);

            if (!gp) {
                if (print) cout << (PR ? "ZIGLEFT\n" : "ZIGRIGHT\n");
                PR ? zigleft(child) : zigright(child);
                return child;
            }

            if (GR && PR) {
                if (print) cout << "ZIGLEFT\n";
                zigleft(par);
                return par;

            } if (!GR && !PR) {
                if (print) cout << "ZIGRIGHT\n";
                zigright(par);
                return par;

            } if (GR && !PR) {
                if (print) cout << "ZIGZAGLEFT\n";
                zigright(child);
                zigleft(child);
                return child;

            } else {
                if (print) cout << "ZIGZAGRIGHT\n";
                zigleft(child);
                zigright(child);
                return child;
            }
        }

        bool isRed(node* n) {
            return n && n->is_red;
        }

        void deleteFix(node* n) {
            node* curr = n;

            while (curr != root && !isRed(curr)) {
                node* parent = curr->parent;
                bool is_left = parent->left == curr;
                node* sibling = is_left? parent->right : parent->left;

                if (isRed(sibling)) {
                    cout << "DELETION Violation: Case 3\n";
                    parent->is_red = true;
                    sibling->is_red = false;
                    is_left ? zigleft(sibling) : zigright(sibling);
                    sibling = is_left ? parent->right : parent->left;
                }

                node* near = is_left ? sibling->left : sibling->right;
                node* far = is_left ? sibling->right : sibling->left;

                if (!isRed(near) && !isRed(far)) {
                    cout << "DELETION Violation: Case 2\n";
                    sibling->is_red = true;
                    curr = parent;
                } else {
                    cout << "DELETION Violation: Case 1\n";
                    if (!isRed(far)) {
                        near->is_red = false;
                        sibling->is_red = true;

                        cout << (is_left? "ZIGRIGHT\n" : "ZIGLEFT\n");
                        is_left ? zigright(near) : zigleft(near);

                        far = is_left ? sibling->right : sibling->left;
                        sibling = is_left ? parent->right : parent->left;
                    }

                    sibling->is_red = parent->is_red;
                    parent->is_red = false;
                    if (far) far->is_red = false;

                    cout << (is_left ? "ZIGLEFT\n" : "ZIGRIGHT\n");
                    is_left ? zigleft(sibling) : zigright(sibling);
                    curr = root;
                }
            }
            if (curr) curr->is_red = false;
        }

    public:
        BSTree() {}

        bool search(int num) {
            if (size == 0) return false;
            return search_node(num, root)->element == num;
        }

        bool insert(int num) {
            if (!root) {
                root = create_node(num, nullptr);
                root->is_red = false;
                size++;
                return true;
            }

            if (search_node(num, root)->element == num) return false;

            node* parent = search_node(num, root);
            node* newNode = create_node(num, parent);
            (num < parent->element ? parent->left : parent->right) = newNode;
            size++;

            while (newNode != root && isRed(newNode) && isRed(parent)) {
                node* uncle = uncleOf(newNode);

                if (!isRed(uncle)) {
                    cout << "UNCLE IS BLACK (RESTRUCTURE & RECOLOR)\n";
                    node* newParent = restructure(newNode, true);
                    newParent->is_red = false;
                    if (newParent->left) newParent->left->is_red = true;
                    if (newParent->right) newParent->right->is_red = true;
                    break;
                }

                if (isRed(uncle)) {
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

        // This function was created in case we are not given a remove function during the exam
        bool REMOVE(int num) {
            if (!root) return false;
            node* rem = search_node(num, root);
            if (!rem || rem->element != num) return false;

            if (rem->left && rem->right) {
                node* suc = rem->right;
                while (suc->left) suc = suc->left;
                rem->element = suc->element;
                rem = suc;
            }

            node* ch = (rem->left) ? rem->left : rem->right;
            bool was_black = isRed(rem);

            if (was_black && !ch) deleteFix(rem);
            transplant(rem, ch);
            if (was_black && ch) deleteFix(ch);

            delete rem;
            size--;
            return true;
        }


        // This function is the same remove function that apppeared during our AVL/SPLAY Tree activity
        // If ever this function is given to us by default during the exam, all we have to do is:

        // MAKE 2 CALLS TO deleteFix IF REM NODE IS NOT RED:
            // Call in 0 children:
                // 1. if(!isRed(rem_node)) deleteFix(rem_node);
            // Call in 1 child:
                // 2. if(!isRed(rem_node)) deleteFix(child);

        // We do not need a call for a 2 child case because the 2 child
        // Because the 2 child case simply recurses and reduces the problem into a 1 child case
        bool remove(int num) {
            if (isEmpty()) {
                return false;
            }
            node* rem_node = search_node(num, root);
            if (rem_node->element != num) {
                return false;
            }

            // FIND the number of children.
            int children = 0;
            // 0 - no children
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

                if (!isRed(rem_node)) deleteFix(rem_node); //CALL HERE

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

                if (!isRed(rem_node)) deleteFix(child); //CALL HERE

                free(rem_node);
                size--;
            } else { // TWO CHILDREN
                node* right_st = rem_node->right;
                while (right_st->left != NULL) {
                    right_st = right_st->left;
                }

                int temp = right_st->element;
                remove(temp);
                rem_node->element = temp;
            }
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
