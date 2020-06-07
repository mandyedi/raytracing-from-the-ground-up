#include "Maths.h"
#include "gtest/gtest.h"

TEST(MathsTest, Max)
{
    EXPECT_EQ(5.0f, max(1.0f, 5.0f));
}