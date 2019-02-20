//
// Created by avbol on 08.12.2018.
//

#ifndef DIFFERENCIATOR_DIFFERENCIATOR_H
#define DIFFERENCIATOR_DIFFERENCIATOR_H

#include "Tree.h"

class Differenciator:Tree{
public:
    Tree* input_tree;
    Tree* output_tree;

    Differenciator();
    Differenciator(Tree* tree);
    ~Differenciator();

    void Diff();
    Node* DiffNode(Node* node);
    void Simplification();

private:
    Node * SimplificationNode(Node* node);
};

#endif //DIFFERENCIATOR_DIFFERENCIATOR_H
