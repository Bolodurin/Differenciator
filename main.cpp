#include <iostream>
#include "Tree.h"
#include "Differenciator.h"

int main() {
    Tree* tree = new Tree();
    assert(tree);
    tree = tree->ReadFromFile();
    assert(tree);
    /*tree->PrintLikeGraph();
    tree->PrintInFile();

    system("dot -Tpng output1.dot > file.png");
    system("start file.png");
    getchar();*/

    Differenciator* differenciator = new
            Differenciator(tree);
    /*differenciator->input_tree->PrintLikeGraph();
    system("dot -Tpng output1.dot > file.png");
    system("start file.png");
    getchar();*/
    differenciator->Diff();
    differenciator->Simplification();
    differenciator->output_tree->PrintLikeGraph();

    system("dot -Tpng output1.dot > file.png");
    system("start file.png");
    getchar();

    return 0;
}