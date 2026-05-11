#ifndef DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H
#define DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H

#include <string>

using namespace std;

struct node {
    char character;
    int weight;
    node* left;
    node* right;
    node* parent;

    node(char c, int w) {
        character = c;
        weight = w;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    string getCode() {
        if(parent == nullptr)
            return "";
        if(this == parent->left)
            return parent->getCode() + "0";
        else
            return parent->getCode() + "1";
    }
};

#endif //DESIGN_AND_ANALYSIS_OF_ALGORITHMS_NODE_H