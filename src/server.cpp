#include <iostream>
#include <unordered_set>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


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


