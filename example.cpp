#include <iostream>
#include <fstream>
#include "randomBinaryTree.hpp"


int main() {
    size_t n = 10;

    TreeNode *root = RandomBinaryTree(n);
    TreeUtil TU(root);

    std::ofstream  ofs ("bt.dot", std::ofstream::out);
    TU.TreeToDot(ofs);

    std::ofstream ofs2 ("bt.txt", std::ofstream::out);
    TU.SimplePrint(ofs2);

    TreeDestroy(root);
    return 0;
}