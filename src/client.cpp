#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


constexpr int BUFFER_SIZE = 1024; //  Since it is marked as constexpr, the compiler will replace all occurrences of BUFFER_SIZE in the code with the value 1024 during the compilation process.


int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error: Failed to create client socket." << std::endl;
        return 1;
    }


    // Set server details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); 
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr)) <= 0) {
        std::cerr << "Error: Invalid server address." << std::endl;
        close(clientSocket);
        return 1;
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Failed to connect to the server." << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Connected to the server." << std::endl;

    // Start user input loop
    std::string command;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        // Send command to server
        ssize_t bytesSent = send(clientSocket, command.c_str(), command.length(), 0);
        if (bytesSent != command.length()) {
            std::cerr << "Error: Failed to send command to server." << std::endl;
            break;
        }

        char buffer[BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));

        // Receive response from server
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            std::cerr << "Error: Failed to receive response from server." << std::endl;
            break;
        }

        std::string response(buffer);
        std::cout << "Server response: " << response << std::endl;
    }

    close(clientSocket);

    return 0;
}


