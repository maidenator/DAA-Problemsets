#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H

#include <algorithm>
using namespace std;
struct node {
    node* parent;
    node* right;
    node* left;
    int elem;

    // TODO paste your height method here
    int height() {
        if(!left && !right) return 1;

        if(!left) return right->height() + 1;

        if(!right) return left->height() + 1;

        else return max(left->height(), right->height()) + 1;
    }
};

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H
