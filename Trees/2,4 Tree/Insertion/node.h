#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H

struct node {
    node* parent;
    int keys[4];
    node** children;
    int size = 0;
};

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H
