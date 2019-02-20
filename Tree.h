//
// Created by avbol on 25.11.2018.
//

#ifndef FIRST_CLION_TREE_H
#define FIRST_CLION_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <assert.h>

#define OUTPUT_FILE "output.txt"
#define INPUT_FILE "input.txt"
#define OUTPUT_DOT_FILE "output1.dot"

enum Type{
    VAR,
    NUM,
    FUNC
};


typedef struct Node
{
    Node* parent;
    Type type;
    char* data;
    Node* left;
    Node* right;

    bool VerificationNode();

    Node();
    Node(char* data_node, Type type1,
            Node* par, Node* lft, Node* rght);
    Node(Node* node);
    ~Node();

    void PrintNodeInFile(FILE *output);
    Node* ReadNodeFromFile(FILE* input,
            char* buffer);
}Node;

class Tree
{
public:
    Node* root;
    int quantity_nodes;

    Tree();
    ~Tree();

    Tree(char* root_el, Type type);
    Tree(Tree* tree);

    bool VerificationTree();

    void PrintLikeGraph();
    void PrintInFile();
    Tree* ReadFromFile();
    void FindParents(Node *pNode);
    void HowNodes(Node* node);

private:
    void RecursPrint(FILE *output, Node *node);
};

#endif //FIRST_CLION_TREE_H
