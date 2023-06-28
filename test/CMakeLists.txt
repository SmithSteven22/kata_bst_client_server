enable_testing()
add_subdirectory(googletest)

add_executable(tests client_test.cpp)
target_link_libraries(tests gtest_main client)
add_test(NAME client_test COMMAND tests)