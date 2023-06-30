#include "gtest/gtest.h"
#include "../src/server.h"
#include <sstream>
#include <iostream>


TEST(TreeNodeTest, InsertNodeTest) {
    TreeNode* root = nullptr;

    // Insert the root node
    root = insertNode(root, 5);
    EXPECT_EQ(root->value, 5);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
