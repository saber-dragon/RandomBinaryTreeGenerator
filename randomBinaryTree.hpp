
#ifndef RANDOMBINARYTREEGENERATOR_RANDOMBINARYTREE_HPP
#define RANDOMBINARYTREEGENERATOR_RANDOMBINARYTREE_HPP

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

//! Class for tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    //! Default constructor
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    //! Constructor specifies the val field
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

//! Overloaded "<<" operator for tree node
/*!
 * This function overloads "<<" for tree node for ease of "printing"
 * a tree node.
 *
 * @param os     output stream
 * @param n      the tree node
 * @return       output stream
 */
std::ostream& operator<<(std::ostream& os, const TreeNode& n){
    os << "{val : " << n.val
       << ", left : " << (n.left ? std::to_string(n.left->val) : "NULL")
       << ", right : " << (n.right ? std::to_string(n.right->val) : "NULL")
       << "}";
    return os;
}

//! Random binary tree generator function
/*!
 * This function generates a random binary tree with n nodes,
 * each of which has a val field within the range of [low, high).
 *
 * @param n             number of nodes
 * @param low           minimum (inclusive) value for the val of a tree node
 * @param high          maximum (exlusive) value for the val of a tree node
 * @return              root of the tree
 */
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

//! Tree destroy function
/*!
 * This function releases the memory of all
 * nodes in a tree recursively.
 *
 * @param root
 */
void TreeDestroy(TreeNode *root) {
    if (root == nullptr) return;
    auto left = root->left;
    auto right = root->right;
    delete root;
    TreeDestroy(left);
    TreeDestroy(right);
}

//! Tree utility class
/*!
 * This class provides many useful APIs which can be applied to a tree.
 *
 */
class TreeUtil {
public:
    TreeNode *root;/*! tree root */
    size_t id;/*! global id */

    //! Constructor
    explicit TreeUtil(TreeNode *root) : root(root), id(0) {}

    //! Tree edge to output stream in dot-format
    /*!
     * This function writes edges of the tree into an output stream.
     *
     * @param os         output stream
     * @param cur        current node
     * @param my_id      id of current node
     */
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
    //! Tree node to output stream in dot-format
    /*!
     * This function writes nodes of the tree into an output stream.
     *
     * @param os         output stream
     * @param cur        current node
     */
    void TreeToDotNode(std::ostream &os, TreeNode *cur) {
        if (cur == nullptr) return;
        os << " node" + std::to_string(id) + "[label = \"<f0> |<f1> " + std::to_string(cur->val) + "|<f2> \"];\n";
        ++id;
        TreeToDotNode(os, cur->left);
        TreeToDotNode(os, cur->right);
    }
    //! Tree to output stream in dot-format
    /*!
     * This function writes the tree into an output stream.
     *
     * @param os         output stream
     */
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

    //! Simple print
    /*!
     * This function simply print all nodes of the tree in
     * the format: {val : cur->val, left : cur->left->val, right
     * : cur->right->val}. Note that if left/right does not
     * exists, a string of "NULL" will be used..
     *
     * @param os       output stream
     */
    void SimplePrint(std::ostream &os) {
        SimplePrintRec(os, root);
    }
    //! Simple print recursively
    /*!
     * This function simply print all nodes of the tree rooted in cur.
     *
     * @param os      output stream
     * @param cur     current node
     */
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
    //! Inorder print
    /*!
     * Similar as SimplePrint"()", but print the tree in an
     * inorder manner.
     *
     * @param os      output stream
     */
    void InorderPrint(std::ostream &os){

        if (root) {
            os << "Inorder Traversal : \n";
            InorderPrintRec(os, root);
        } else {
            os << "Got an empty tree, nothing to print!\n";
        }
    }
    //! Inorder print recursively
    void InorderPrintRec(std::ostream &os, TreeNode *cur){
        if (cur->left) InorderPrintRec(os, cur->left);
        os << (*cur) << "\n";
        if (cur->right) InorderPrintRec(os, cur->right);
    }
};


#endif //RANDOMBINARYTREEGENERATOR_RANDOMBINARYTREE_HPP
