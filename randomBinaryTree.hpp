
#ifndef RANDOMBINARYTREEGENERATOR_RANDOMBINARYTREE_HPP
#define RANDOMBINARYTREEGENERATOR_RANDOMBINARYTREE_HPP

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};


TreeNode *RandomBinaryTree(size_t n, int low = 0, int high = 10000) {
    if (n == 0) return nullptr;
    std::vector<TreeNode *> UnsaturatedNodes(n, nullptr);
    int Candidate = 0;
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int rVal = std::rand() % (high - low) + low;
    TreeNode *root = new TreeNode(rVal);
    --n;
    ++Candidate;
    UnsaturatedNodes[0] = root;

    while (n != 0) {
        auto SIndex = std::rand() % Candidate;
        auto Selected = UnsaturatedNodes[SIndex];
        rVal = std::rand() % (high - low) + low;
        auto *NewNode = new TreeNode(rVal);
        if (!Selected->left && !Selected->right) {//
            if (std::rand() % 2 == 0) Selected->left = NewNode;
            else Selected->right = NewNode;
            UnsaturatedNodes[Candidate++] = NewNode;
        } else {
            if (Selected->left) {
                Selected->right = NewNode;
            } else if (Selected->right) {
                Selected->left = NewNode;
            }
            UnsaturatedNodes[SIndex] = UnsaturatedNodes[Candidate - 1];
            UnsaturatedNodes[Candidate - 1] = NewNode;
        }
        --n;
    }

    return root;
}

void TreeDestory(TreeNode *root) {
    if (root == nullptr) return;
    auto left = root->left;
    auto right = root->right;
    delete root;
    TreeDestory(left);
    TreeDestory(right);
}


class TreeUtil {
public:
    TreeNode *root;
    size_t id;

    explicit TreeUtil(TreeNode *root) : root(root), id(0) {}


    void TreeToDotEdge(std::ostream &os, TreeNode *cur, size_t my_id) {
        id = my_id;
        if (cur->left) {
            size_t my_left = my_id + 1;
            os << "\"node" + std::to_string(my_id) + "\":f0 -> \"node" + std::to_string(my_left) + "\":f1;\n";
            TreeToDotEdge(os, cur->left, my_left);
        }
        if (cur->right) {
            size_t my_right = id + 1;
            os << "\"node" + std::to_string(my_id) + "\":f2 -> \"node" + std::to_string(my_right) + "\":f1;\n";
            TreeToDotEdge(os, cur->right, my_right);
        }
    }

    void TreeToDotNode(std::ostream &os, TreeNode *cur) {
        if (cur == nullptr) return;
        os << " node" + std::to_string(id) + "[label = \"<f0> |<f1> " + std::to_string(cur->val) + "|<f2> \"];\n";
        ++id;
        TreeToDotNode(os, cur->left);
        TreeToDotNode(os, cur->right);
    }

    void TreeToDot(std::ostream &os) {
        if (root == nullptr) return;
        os << "digraph BinaryTree {\n";
        os << "node [shape = record,height=.1];\n";
        id = 0;
        TreeToDotNode(os, root);
        id = 0;// reset id
        TreeToDotEdge(os, root, 0);

        os << "}\n";
    }


    void SimplePrint(std::ostream &os) {
        SimplePrintRec(os, root);
    }

    void SimplePrintRec(std::ostream &os, TreeNode *cur) {
        if (cur == nullptr) return;
        os << "{val : "
           << cur->val
           << ", left : "
           << (cur->left ? std::to_string(cur->left->val) : "NULL")
           << ", right : "
           << (cur->right ? std::to_string(cur->right->val) : "NULL")
           << "}\n";
        SimplePrintRec(os, cur->left);
        SimplePrintRec(os, cur->right);
    }
};


#endif //RANDOMBINARYTREEGENERATOR_RANDOMBINARYTREE_HPP
