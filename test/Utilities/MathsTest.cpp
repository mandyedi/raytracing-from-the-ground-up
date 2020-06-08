#include "gtest/gtest.h"
#include "Maths.h"

TEST(MathsTest, Max) {
    EXPECT_EQ(5.0, max(1.0, 5.0));
    EXPECT_EQ(5.0, max(5.0, 1.0));
    EXPECT_EQ(-1.0, max(-1.0, -5.0));
    EXPECT_EQ(-1.0, max(-5.0, -1.0));
    EXPECT_EQ(1.0, max(1.0, -5.0));
    EXPECT_EQ(1.0, max(-5.0, 1.0));
    EXPECT_EQ(5.0, max(0.0, 5.0));
    EXPECT_EQ(5.0, max(5.0, 0.0));
    EXPECT_EQ(0.0, max(0.0, -5.0));
    EXPECT_EQ(0.0, max(-5.0, 0.0));

    EXPECT_EQ(5.0f, max(1.0f, 5.0f));
    EXPECT_EQ(5.0f, max(5.0f, 1.0f));
    EXPECT_EQ(-1.0f, max(-1.0f, -5.0f));
    EXPECT_EQ(-1.0f, max(-5.0f, -1.0f));
    EXPECT_EQ(1.0f, max(1.0f, -5.0f));
    EXPECT_EQ(1.0f, max(-5.0f, 1.0f));
    EXPECT_EQ(5.0f, max(0.0f, 5.0f));
    EXPECT_EQ(5.0f, max(5.0f, 0.0f));
    EXPECT_EQ(0.0f, max(0.0f, -5.0f));
    EXPECT_EQ(0.0f, max(-5.0f, 0.0f));
}
