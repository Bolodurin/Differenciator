//
// Created by avbol on 08.12.2018.
//

#include "Differenciator.h"

#define ISNULLLEFT (node->left->type == NUM && strtod(node->left->data, endstr) == 0)
#define ISNULLRIGHT (node->right->type == NUM && strtod(node->right->data, endstr) == 0)
#define ISONELEFT node->left->type == NUM && strtod(node->left->data, endstr) == 1
#define ISONERIGHT node->right->type == NUM && strtod(node->right->data, endstr) == 1
#define ISNUMBERS (node->left->type == NUM && node->right->type == NUM)

Differenciator::Differenciator() {
    this->input_tree = this->
            input_tree->ReadFromFile();
    this->output_tree = nullptr;
}

Differenciator::Differenciator(Tree* tree) : Tree(tree) {
    this->input_tree = new Tree(tree);
    this->output_tree = nullptr;
}

Differenciator::~Differenciator() {
    delete(this->input_tree);
    delete(this->output_tree);
}

void Differenciator::Diff() {
    if(!this->input_tree->VerificationTree())
        printf("ERROR in input tree to diff\n");

    this->output_tree = new Tree();
    this->output_tree->root = DiffNode(
            this->input_tree->root);
    this->output_tree->HowNodes(
            this->output_tree->root);

    this->output_tree->PrintInFile();
    this->output_tree->PrintLikeGraph();

    /*system("dot -Tpng output1.dot > file.png");
    system("start file.png");
    getchar();*/
    assert(output_tree);
    assert(output_tree->VerificationTree());
}

Node* Differenciator::DiffNode(Node* node) {
    Node* out_node = new Node();
    if(node->type == NUM)
    {
        char nil_str[2] = "0";
        out_node = new Node(nil_str, NUM,
                nullptr, nullptr, nullptr);
    }
    else if(node->type == VAR)
    {
        char one_str[2] = "1";
        out_node = new Node(one_str, NUM,
                            nullptr, nullptr, nullptr);
    }
    else if(node->left && node->right)
    {
        #define DIFF_DEF(name, code)               \
        else if(strcmp(node->data, #name) == 0)    \
            code

        if(false){}
        #include "BinaryFunctions.h"

        #undef DIFF_DEF
    }
    else if(!node->left && node->right)
    {
        #define DIFF_DEF(name, code)               \
        else if(strcmp(node->data, #name) == 0)    \
            code

        if(false){}
        #include "UnaryFunctions.h"

        #undef DIFF_DEF
    }

    return out_node;
}

void Differenciator::Simplification() {
    assert(this->input_tree->VerificationTree());

    int quantity_of_nodes = 0;
    this->output_tree->quantity_nodes = 0;
    this->output_tree->HowNodes(this->output_tree->root);
    quantity_of_nodes = this->output_tree->quantity_nodes;

    this->output_tree->root = SimplificationNode(
            this->output_tree->root);
    printf("Successful simplification\n");
    assert(this->output_tree->root);

    this->output_tree->quantity_nodes = 0;

    this->output_tree->HowNodes(this->output_tree->root);
    assert(this->output_tree->VerificationTree());

    printf("Successful HowNodes\n");
    this->output_tree->PrintLikeGraph();
    if(quantity_of_nodes != this->output_tree->quantity_nodes)
        Simplification();

    /*system("dot -Tpng output1.dot > file.png");
    system("start file.png");*/
    assert(this->output_tree->VerificationTree());
}

Node * Differenciator::SimplificationNode(Node *node) {
    char** endstr = nullptr;
    //printf("1::%p---     %s\n", node->left,node->data);
    Node* new_node = new Node();

    if(node->type == NUM || node->type == VAR)
        return node;
    else if(node->type == FUNC)
    {
        if(strcmp(node->data, "+") == 0 ||
           strcmp(node->data, "-") == 0)
        {
            if(ISNULLRIGHT)
            {
                new_node = new Node(node->left->data,
                                    node->left->type,
                                    nullptr, node->left->left,
                                    node->left->right);
                printf("NullRight\n");
            }
            else if(ISNULLLEFT)
            {
                new_node = new Node(node->right->data,
                                    node->right->type,
                                    nullptr, node->right->left,
                                    node->right->right);
            }
            else if(ISNUMBERS)
            {
                double left_number = strtod(node->left->data, endstr);
                double right_number = strtod(node->right->data, endstr);

                if(strcmp(node->data, "+") == 0)
                {
                    char str[20] = "";
                    sprintf(str, "%lf", left_number+right_number);
                    new_node = new Node(str, NUM,
                                        nullptr, nullptr, nullptr);
                }
                else if(strcmp(node->data, "-") == 0)
                {
                    char str[20] = "";
                    sprintf(str, "%lf", left_number-right_number);
                    new_node = new Node(str, NUM,
                                        nullptr, nullptr, nullptr);
                }
            }
            else    new_node = new Node(node);
        }
        else if(strcmp(node->data, "*") == 0)
        {
            if(ISNULLRIGHT || ISNULLLEFT)
            {
                char null_str[2] = "0";
                new_node = new Node(null_str, NUM,
                                    nullptr, nullptr, nullptr);
            }
            else if(ISONELEFT)
            {
                new_node = new Node(node->right->data,
                                    node->right->type,
                                    nullptr, node->right->left,
                                    node->right->right);
            }
            else if(ISONERIGHT)
            {
                new_node = new Node(node->left->data,
                                    node->left->type,
                                    nullptr, node->left->left,
                                    node->left->right);
            }
            else      new_node = new Node(node);
        }
        else if(strcmp(node->data, "/") == 0)
        {
            if(ISNULLLEFT)
            {
                char null_str[2] = "0";
                new_node = new Node(null_str, NUM,
                                    nullptr, nullptr, nullptr);
            }
            else if(ISONERIGHT)
            {
                new_node = new Node(node->left->data,
                                    node->left->type,
                                    nullptr, node->left->left,
                                    node->left->right);
            }
            else if(ISNULLRIGHT)
            {
                printf("ERROR with tree, find in Simplification\n");
            }
            else      new_node = new Node(node);
        }
        else     new_node = new Node(node);

        //printf("%p %p:    %s %p\n", new_node, new_node->left,
        //        new_node->left->data, new_node->left->left);
        //printf("2::%s\n", new_node->data);
        if(new_node->left){
            assert(new_node->left);
            new_node->left = SimplificationNode(new_node->left);
            assert(new_node->left);
        }

        if(new_node->right)
        {
            assert(new_node->right);
            new_node->right = SimplificationNode(new_node->right);
            assert(new_node->right);
        }

        return new_node;
    }
    printf("Some ERROR\n");
    return nullptr;
}
