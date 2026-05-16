    #ifndef TREES_TREE_H
    #define TREES_TREE_H

    #include "node.h"
    #include <iostream>
    using namespace std;
    class BSTree {
        node* root = nullptr;
        int size = 0;

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
        node* search_node(int num, node* curr) {
            if (curr->element == num) return curr;
            node* next = (num < curr->element) ? curr->left : curr->right;
            return next ? search_node(num, next) : curr;
        }

        //Replaces a node x with y
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

            // NO GP
            if (!gp) {
                if (print) cout << (PR ? "ZIGLEFT\n" : "ZIGRIGHT\n");
                PR ? zigleft(child) : zigright(child);
                return child;
            }

            if (GR && PR) {             // RR
                if (print) cout << "ZIGLEFT\n";
                zigleft(par);
                return par;

            } if (!GR && !PR) {    // LL
                if (print) cout << "ZIGRIGHT\n";
                zigright(par);
                return par;

            } if (GR && !PR) {     // RL
                if (print) cout << "ZIGZAGLEFT\n";
                zigright(child);
                zigleft(child);
                return child;

            } else {                    // LR
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
                node* p = curr->parent;
                bool is_left = curr == p->left;

                // 1. Identify sibling based on our position
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

                // 2. Identify nephews based on our position
                node* near = is_left ? sibling->left : sibling->right;
                node* far = is_left ? sibling->right : sibling->left;

                // CASE 2: Sibling is Black & black children: PUSH UP BLACKNESS
                if (!isRed(near) && !isRed(far)) {
                    cout << "DELETION Violation: Case 2\n";
                    sibling->is_red = true;
                    curr = p;
                }

                // CASE 1: Sibling is Black & 1 Red Nephew
                else {
                    cout << "DELETION Violation: Case 1\n";
                    // Subcase: Near Nephew is Red
                    if (!isRed(far)) {
                        near->is_red = false;
                        sibling->is_red = true;

                        is_left ? zigright(near) : zigleft(near);
                        cout << (is_left? "ZIGRIGHT\n" : "ZIGLEFT\n");

                        // Update pointers after straightening
                        sibling = is_left ? p->right : p->left;
                        far = is_left ? sibling->right : sibling->left;
                    }
                    // Subcase: Far Nephew is Red
                    sibling->is_red = p->is_red;     // Sibling takes parent's color
                    p->is_red = false;               // Parent becomes Black
                    if (far) far->is_red = false;    // Far Nephew becomes Black

                    restructure(sibling, true); // The final balancing rotation
                    curr = root;                     // Force the loop to terminate
                }
            }
            // Ensure the final node (or root) is Black
            if (curr) curr->is_red = false;
        }

    public:
        BSTree() {}

        bool search(int num) {
            return search_node(num, root)->element == num;
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
            if (search_node(num, root)->element == num) return false;

            //2. Insert to its rightful place
            node* parent = search_node(num, root);
            node* newNode = create_node(num, parent);
            (num < parent->element ? parent->left : parent->right) = newNode;
            size++;

            //3. Check for violations
            while (newNode != root && newNode->is_red && parent->is_red) {
                node* uncle = uncleOf(newNode);

                if (uncle == nullptr || !uncle->is_red) {
                    cout << "UNCLE IS BLACK (RESTRUCTURE & RECOLOR)\n";
                    node* newParent = restructure(newNode, true);
                    newParent->is_red = false;
                    if (newParent->left) newParent->left->is_red = true;
                    if (newParent->right) newParent->right->is_red = true;
                    break;
                }

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

        bool remove(int num) {
            //0. ROOT
            if (!root) return false;
            node* rem = search_node(num, root);
            if (!rem || rem->element != num) return false;

            //1. 2-CHILD CASE
            if (rem->left && rem->right) {
                node* suc = rem->right;
                while (suc->left) suc = suc->left;
                rem->element = suc->element;
                rem = suc;
            }

            //2. 1-CHILD CASE
            //2.1 child and rem's color
            node* ch = (rem->left) ? rem->left : rem->right;
            bool was_black = !rem->is_red;

            //2.2 no ch? fix rem t(r,c) yes ch? fix ch
            if (was_black && !ch) deleteFix(rem);
            transplant(rem, ch);
            if (was_black && ch) deleteFix(ch);

            //3. DELETE
            delete rem;
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
