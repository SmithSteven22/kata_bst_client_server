#include "gtest/gtest.h"
#include "../src/client.h"


// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(factorial(0), 1);
}

