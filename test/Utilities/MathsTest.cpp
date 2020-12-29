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

TEST(MathsTest, DegreeToRadian) {
    EXPECT_FLOAT_EQ(degreeToRadian(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(degreeToRadian(90.0f), 1.570796f);
    EXPECT_FLOAT_EQ(degreeToRadian(180.0f), 3.141592f);
    EXPECT_FLOAT_EQ(degreeToRadian(360.0f), 6.283185f);
    EXPECT_FLOAT_EQ(degreeToRadian(540.0f), 9.424777f);
    EXPECT_FLOAT_EQ(degreeToRadian(-180.0f), -3.141592f);
}

TEST(MathsTest, RadianToDegree) {
    EXPECT_FLOAT_EQ(radianToDegree(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(radianToDegree(1.570796f), 90.0f);
    EXPECT_FLOAT_EQ(radianToDegree(3.141592f), 180.0f);
    EXPECT_FLOAT_EQ(radianToDegree(6.283185f), 360.0f);
    EXPECT_FLOAT_EQ(radianToDegree(9.424777f), 540.0f);
    EXPECT_FLOAT_EQ(radianToDegree(-3.141592f), -180.0f);
}