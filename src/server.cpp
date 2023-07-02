#include <iostream>
#include <unordered_set>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
// https://marketsplash.com/tutorials/cpp/cplusplus-scoket/


constexpr int BUFFER_SIZE = 1024; //  Since it is marked as constexpr, the compiler will replace all occurrences of BUFFER_SIZE in the code with the value 1024 during the compilation process.

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

TreeNode* deleteNode(TreeNode* node, int value);

TreeNode* findMin(TreeNode* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

TreeNode* deleteNode(TreeNode* node, int value) {
    if (node == nullptr)
        return nullptr;

    if (value < node->value)
        node->left = deleteNode(node->left, value);
    else if (value > node->value)
        node->right = deleteNode(node->right, value);
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        } else {
            TreeNode* minRight = findMin(node->right);
            node->value = minRight->value;
            node->right = deleteNode(node->right, minRight->value);
        }
    }

    return node;
}


bool findNode(TreeNode* node, int value) {
    if (node == nullptr)
        return false;

    if (value == node->value)
        return true;
    else if (value < node->value)
        return findNode(node->left, value);
    else
        return findNode(node->right, value);
}

void handleClient(int clientSocket) {
    TreeNode* root = nullptr;
    char buffer[BUFFER_SIZE];

    while (true) {
        // Clear buffer
        memset(buffer, 0, sizeof(buffer));

        // Receive command from client
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            std::cerr << "Error: Failed to receive data from client." << std::endl;
            break;
        }

        std::string command(buffer);

        // Parse command
        std::istringstream iss(command);
        std::string cmd, valueStr;
        iss >> cmd >> valueStr;

        std::string response;

        if (cmd == "insert") {
            int value = std::stoi(valueStr);
            root = insertNode(root, value);
            // std::cout << "Inserted " << value << " into the BST." << std::endl;
            response = "Inserted " + valueStr + " into the BST.";
        } else if (cmd == "delete") {
            int value = std::stoi(valueStr);
            root = deleteNode(root, value);
            // std::cout << "Deleted " << value << " from the BST." << std::endl;
            response = "Deleted " + valueStr + " from the BST.";
        } else if (cmd == "find") {
            int value = std::stoi(valueStr);
            bool found = findNode(root, value);
            if (found)
                // std::cout << value << " found in the BST." << std::endl;
                response = valueStr + " found in the BST.";
            else
                // std::cout << value << " not found in the BST." << std::endl;
                response = valueStr + " not found in the BST.";
        } else {
            // std::cerr << "Error: Invalid command." << std::endl;
            response = "Error: Invalid command.";
        }

        // Send response to client
        // std::string response = "OK";
        ssize_t bytesSent = send(clientSocket, response.c_str(), response.length(), 0);
        if (bytesSent != response.length()) {
            std::cerr << "Error: Failed to send response to client." << std::endl;
            break;
        }
    }

    close(clientSocket);
}


int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error: Failed to create server socket." << std::endl;
        return 1;
    }

    // Bind socket to port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080); 

    if (bind(serverSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Failed to bind server socket to port." << std::endl;
        close(serverSocket);
        return 1;
    }

    // Listen for connections
    if (listen(serverSocket, 1) == -1) {
        std::cerr << "Error: Failed to listen for connections." << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server started. Listening for connections..." << std::endl;

    // Accept incoming connections
    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddr, &clientAddrSize);
        if (clientSocket == -1) {
            std::cerr << "Error: Failed to accept incoming connection." << std::endl;
            break;
        }

        std::cout << "Accepted new connection." << std::endl;

        // Handle client in a separate thread
        handleClient(clientSocket);
    }

    close(serverSocket);

    return 0;
}


