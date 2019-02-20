//
// Created by avbol on 25.11.2018.
//


#include "Tree.h"

bool Tree::VerificationTree() {
    assert(root);
    return root->VerificationNode();
}

bool Node::VerificationNode(){
    assert(this);
    return this->data &&
        (this->left ? this->left->VerificationNode() : true) &&
        (this->right ? this->right->VerificationNode() : true);
};

Tree::Tree() {
    quantity_nodes = 0;
    root = nullptr;
}

Node::Node(){
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = nullptr;
}

Node::Node(char* data_node, Type type1, Node* par = nullptr,
        Node* lft = nullptr, Node* rght = nullptr) {
    if(!data_node)
    {
        printf("ERROR with creating node\n");
        assert(nullptr);
    }

    this->data = strdup(data_node);
    this->type = type1;
    this->parent = par;
    this->left = lft;
    this->right = rght;
}

Node::Node(Node* node)
{
    this->data = strdup(node->data);
    this->type = node->type;

    if(node->left)
    {
        this->left = new Node(node->left);
        this->left->parent = this;
    }
    else
        this->left = nullptr;
    if(node->right)
    {
        this->right = new Node(node->right);
        this->right->parent = this;
    }
    else
        this->right = nullptr;
}

Node::~Node() {
    if(this->left)   delete(this->left);
    if(this->right)  delete(this->right);

    free(this->data);
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

Tree::Tree(char* root_el, Type type) {
    root = new Node(root_el, type);
    this->quantity_nodes = 1;
}

Tree::~Tree() {
    delete(this->root);
    this->quantity_nodes = 0;
}

void Node::PrintNodeInFile(FILE *output) {

    fprintf(output, "(");

    if(this->left)
        this->left->PrintNodeInFile(output);

    fprintf(output, "%s", this->data);

    if(this->right)
        this->right->PrintNodeInFile(output);

    fprintf(output, ")");
}

void Tree::PrintInFile() {
    FILE* output = fopen(OUTPUT_FILE, "w");
    assert(output);

    if (VerificationTree())  root->PrintNodeInFile(output);
    else                     printf("ERROR with tree in PrintInFile");

    fclose(output);
}

void Tree::PrintLikeGraph() {
    if(!VerificationTree())
    {
        printf("ERROR in tree!\n");
    }

    FILE* output = fopen(OUTPUT_DOT_FILE, "w");
    assert(output);

    fprintf(output, "digraph BST {\n");
    fprintf(output, "    node [fontname=\"Arial\"];\n");

    if(!root)    fprintf(output, "\n");
    else         RecursPrint(output, root);

    fprintf(output, "}");
    fclose(output);
}

void Tree::RecursPrint(FILE* output, Node* node) {
    assert(output && node);
    static int nullcount = 0;

    //printf("12::%p %p %s\n", node->left, node->right, node->data);
    if(node->left)
    {
        fprintf(output, "    \"%p: %s\"->\"%p: %s\";\n",
                node, node->data, node->left, node->left->data);
        RecursPrint(output, node->left);
    }
    else
    {
        fprintf(output, "    null%d [shape=point];\n", nullcount);
        fprintf(output, "    \"%p: %s\"->null%d;\n", node, node->data, nullcount);
        nullcount++;
    }

    if(node->right)
    {
        fprintf(output, "    \"%p: %s\"->\"%p: %s\";\n",
                node, node->data, node->right, node->right->data);
        RecursPrint(output, node->right);
    }
    else
    {
        fprintf(output, "    null%d [shape=point];\n", nullcount);
        fprintf(output, "    \"%p: %s\"->null%d;\n", node, node->data, nullcount);
        nullcount++;
    }
}

Tree::Tree(Tree *tree):
    quantity_nodes(tree->quantity_nodes){
    root = new Node(tree->root);
}

int current_position = 0;

Node* Node::ReadNodeFromFile(FILE* input,
        char* buffer) {
    assert(input);
    assert(buffer);
    Node* node = new Node();
    assert(buffer);

    if(buffer[current_position+1] == '(')
    {
        current_position++;
        node->left = node->left->
                ReadNodeFromFile(input, buffer);
    }

    current_position++;
    char curr_str[100] = "";
    int curr_symbol = 0;

    while (buffer[current_position] != '(' &&
            buffer[current_position] != ')')
    {
        curr_str[curr_symbol] = buffer[current_position];
        curr_str[curr_symbol+1] = '\0';
        curr_symbol++;
        current_position++;
    }
    //printf("2::%s\n", buffer+current_position-1);

    node->data = strdup(curr_str);
    char** remainder = nullptr;
    if(strtod(curr_str, remainder) != 0 ||
        curr_str[0] == '0')
    {
        node->type = NUM;
    }
    else if(curr_str[0] == 'x')
        node->type = VAR;
    else
        node->type = FUNC;

    if(buffer[current_position] == '(')
    {
        node->right = node->right->
                ReadNodeFromFile(input, buffer);
        current_position++;
    }


    return node;
}

int quantity_of_nodes = 0;

Tree* Tree::ReadFromFile() {
    FILE* input = fopen(INPUT_FILE, "r");
    assert(input);

    Tree* tree = new Tree();
    char buffer[10000] = "";
    fscanf(input, "%[^\n]", buffer);
    assert(buffer);
    printf("%s\n", buffer);

    tree->root = tree->root->ReadNodeFromFile(input, buffer);
    tree->FindParents(tree->root);

    tree->quantity_nodes = quantity_of_nodes;
    assert(tree->VerificationTree());

    fclose(input);
    return tree;
}

void Tree::FindParents(Node* node) {
    assert(node);
    quantity_of_nodes++;
    if(node->left)
    {
        node->left->parent = node;
        FindParents(node->left);
    }

    if(node->right)
    {
        node->right->parent = node;
        FindParents(node->right);
    }
}

void Tree::HowNodes(Node *node) {
    assert(node);
    //printf("Now111: %d ", this->quantity_nodes);
    this->quantity_nodes++;
    //printf("Now: %d\n", this->quantity_nodes);

    //printf("Data: %s\n", node->data);
    if(node->left)
        HowNodes(node->left);
    if(node->right)
        HowNodes(node->right);

}




