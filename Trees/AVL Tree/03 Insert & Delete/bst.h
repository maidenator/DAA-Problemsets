#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_BST_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_BST_H

#include "mybinarytree.hpp"

class BST {
	BinaryTree* tree = new MyBinaryTree();

	public:
	bool search(int num) {
		return search_node(tree->getRoot(), num);
	}

	bool search_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
			return true;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num);
		} else {
			return search_node(n->left, num);
		}
	}



    // TODO perform post-processing by checking for violation after insertion
    // from the node inserted (or from its parent) until the root
	void postProcess(node* n) {
		for(node* curr = n; curr; curr = curr->parent)
			restructure(curr);
	}

	node* insert(int num) {
        node* n = tree->getRoot();
        if (n == NULL) {
            return tree->addRoot(num);
        }
        return insert_node(n, num);
    }

	node* insert_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
			return NULL;
		}
		if (num > n->elem) {
			if (!n->right) {
				node* added = tree->addRight(n, num);
				postProcess(n);
				return added;
			} else {
				return insert_node(n->right, num);
			}
		} else {
			if (!n->left) {
				node* added = tree->addLeft(n, num);
				postProcess(n);
				return added;
			} else {
				return insert_node(n->left, num);
			}
		}
	}


    // TODO perform post-processing by checking for violation after deletion
    // from the parent of the node removed until the root
    bool remove(int num) {
        return remove_node(tree->getRoot(), num);
    }

	bool remove_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
		    node* parent = NULL;
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                parent = r->parent;
                int rem = tree->remove(r);
                n->elem = rem;
            } else {
                parent = n->parent;
    			tree->remove(n);
            }
            if(parent) postProcess(parent);
            return true;
		}
		if (num > n->elem) {
			return remove_node(n->right, num);
		} else {
			return remove_node(n->left, num);
		}
	}

    // TODO copy and paste your completed restructure method here

	//UTILITY
    int getHeight(node* n) {
        return n? n->height() : 0;
    }

	//UTILITY
    int getBF(node* n) {
        return n? getHeight(n->left) - getHeight(n->right) : 0;
    }
    bool restructure(node* gp) {
        if(!gp) return false;
        int gbf = getBF(gp);

        if(gbf > -2 && gbf < 2)
            return false;

        node* par; // parent
        // TODO find parent

        if(gbf >= 1) {
            par = gp->left;
        } else if(gbf <= -1) {
            par = gp->right;
        }


        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        node* child;
        // TODO find child
        int pbf = getBF(par);
        if(pbf == 0) {
            if(gtop_right) {
                child = par->right;
            } else {
                child = par->left;
            }
        } else if(pbf >= 1) {
            child = par->left;
        } else {
            child = par->right;
        }


        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

        // z
        //  \
        //   y
        //    \
        //     x
        if (gtop_right && ptoc_right) {
            // TODO call to either zigleft or zigright or both
            cout<<"ZIGLEFT\n";
            zigleft(par);
        }

        // z
        //   \
        //     y
        //    /
        //   x
        else if (gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            cout<<"ZIGZAGLEFT\n";
            zigright(child);
            zigleft(child);
        }

        //     z
        //    /
        //   y
        //  /
        // x
        else if (!gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            cout<<"ZIGRIGHT\n";
            zigright(par);
        }

        //      z
        //    /
        //  y
        //   \
        //    x
        else {
            // TODO call to either zigleft or zigright or both
            cout<<"ZIGZAGRIGHT\n";
            zigleft(child);
            zigright(child);
        }

        return true;
    }

    void zigleft(node* curr) {
        tree->zigleft(curr);
    }

    void zigright(node* curr) {
        tree->zigright(curr);
    }

	void print() {
		tree->print();
	}
};

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_BST_H
