#include <iostream>
#include <fstream>
#include "randomBinaryTree.hpp"

using namespace std;


bool InorderSuccessorRec(TreeNode* cur, const TreeNode* p, TreeNode *& pre, TreeNode*& res){
    if (res) return true;// already found, no need to explore further
    // visit left sub-tree
    if (cur->left && InorderSuccessorRec(cur->left, p, pre, res)) return true;
    // check whether my predecessor is p
    if (pre == p) { res = cur; return true; }
    // visit me
    pre = cur;
    // visit right sub-tree
    return cur->right && InorderSuccessorRec(cur->right, p, pre, res);
}

TreeNode *InorderSuccessor(TreeNode* root, TreeNode* p){
    if (root == nullptr) return nullptr;
    TreeNode *res = nullptr;
    TreeNode *pre = nullptr;
    InorderSuccessorRec(root, p, pre, res);
    return res;
}


int main(){
    size_t n = 10;

    TreeNode *root = RandomBinaryTree(n);
    TreeUtil TU(root);

    std::ofstream  ofs ("bt.dot", std::ofstream::out);
    TU.TreeToDot(ofs);

    std::vector<TreeNode *> TestNodes;
    size_t c = 0;
    TestNodes.push_back(root);

    while (c < TestNodes.size()){
        auto Current = TestNodes[c];
        if (Current->left) TestNodes.push_back(Current->left);
        if (Current->right) TestNodes.push_back(Current->right);
        ++ c;
    }

    TU.InorderPrint(std::cout);
    std::cout << "\n---------------------------------------------------------\n\n";

    for (auto& TestNode : TestNodes){
        auto next = InorderSuccessor(root, TestNode);
        if (next) std::cout << "Successor of " << (*TestNode) << " is " << (*next) << std::endl;
        else std::cout << (*TestNode) << " has no successor!\n";
    }

    TreeDestroy(root);

    return 0;

}