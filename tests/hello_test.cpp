#include "hello.h"

#include <gtest/gtest.h>

TEST(HelloTest, ReturnsExpectedGreeting) {
    EXPECT_EQ(make_greeting(), "Hello from C++ in Jenkins!");
}