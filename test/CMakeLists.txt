enable_testing()
add_subdirectory(googletest)


# Server
add_executable(server_test server_test.cpp)
target_link_libraries(server_test gtest_main server)
add_test(NAME server_test COMMAND server_test)

# Client
add_executable(client_test client_test.cpp)
target_link_libraries(client_test gtest_main client)
add_test(NAME client_test COMMAND client_test)