### kata_bst_client_server
# Binary search tree
The server "**server.cpp**" receives the commands below from the client "**client.cpp**" and sends a response respectively.
-  **insert <n>:** Insert the integer n into the BST. If n is already in the BST, print an error message on standard err. 
-  **delete <n>:** Delete the integer n from the BST. If n is not in the BST, print an error message on standard err. 
-  **find <n>:** Find whether n is in the BST and respond with either found or not found.

  
![leil](https://github.com/SmithSteven22/kata_bst_client_server/blob/main/media/leil.gif)

Similarly to the **client files:**
-  **server.h:** contains functions to test
-  **server_test.cpp:** test cases
-  **server.cpp:** final solution

# TDD is slow (^_^)

# Thread
To create a multithreaded version of the solution, threading would be introduced by including **<thread>** to simultaneously handle the user input and the communication with the server. 

### References
[1] https://marketsplash.com/tutorials/cpp/cplusplus-scoket/


[2] https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/


