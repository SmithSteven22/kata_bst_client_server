#include <iostream>
#include <unordered_set>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>


// constexpr int BUFFER_SIZE = 1024; //  Since it is marked as constexpr, the compiler will replace all occurrences of BUFFER_SIZE in the code with the value 1024 during the compilation process.

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

TreeNode* insertNode(TreeNode* node, int value) {
    if (node == nullptr)
        return new TreeNode(value);

    if (value < node->value)
        node->left = insertNode(node->left, value);
    else if (value > node->value)
        node->right = insertNode(node->right, value);

    return node;
}

int main(){
    std::cout <<"Hello \n";
}

