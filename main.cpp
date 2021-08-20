#include <iostream>
#include "include/bstree.h"

using namespace forest;
//TODO - optional - pass same type data between different trees
int main()
{
    bstree::tree<int> binary_tree;

    //simple benachmark

    binary_tree.insert(100);
    binary_tree.insert(55);
    binary_tree.insert(101);
    binary_tree.insert(12);
    binary_tree.insert(64);
    binary_tree.traverse();
    std::cout << "remove 64" << std::endl;
    binary_tree.remove(64);
    binary_tree.traverse();
    std::cout << "remove 101" << std::endl;
    binary_tree.remove(101);
    binary_tree.traverse();

}