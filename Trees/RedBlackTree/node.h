#ifndef TREES_NODE_H
#define TREES_NODE_H

#include <iostream>
using namespace std;
struct node {
    bool is_red;
    int element;
    node* left;
    node* right;
    node* parent;
};

#endif //TREES_NODE_H
