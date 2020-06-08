#include "gtest/gtest.h"
#include "RGBColor.h"

TEST(RGBColorTest, Initialization) {
    RGBColor c0;
    EXPECT_FLOAT_EQ(0.0f, c0.r);
    EXPECT_FLOAT_EQ(0.0f, c0.g);
    EXPECT_FLOAT_EQ(0.0f, c0.b);

    RGBColor c1(1.0f);
    EXPECT_FLOAT_EQ(1.0f, c1.r);
    EXPECT_FLOAT_EQ(1.0f, c1.g);
    EXPECT_FLOAT_EQ(1.0f, c1.b);

    RGBColor c2(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(1.0f, c2.r);
    EXPECT_FLOAT_EQ(2.0f, c2.g);
    EXPECT_FLOAT_EQ(3.0f, c2.b);

    RGBColor c3(c2);
    EXPECT_FLOAT_EQ(1.0f, c3.r);
    EXPECT_FLOAT_EQ(2.0f, c3.g);
    EXPECT_FLOAT_EQ(3.0f, c3.b);

    RGBColor c4;
    c4 = c2;
    EXPECT_FLOAT_EQ(1.0f, c4.r);
    EXPECT_FLOAT_EQ(2.0f, c4.g);
    EXPECT_FLOAT_EQ(3.0f, c4.b);
}

TEST(RGBColorTest, MathOperations) {
    RGBColor c0(1.0f, 2.0f, 3.0f);
    RGBColor c1(4.0f, 5.0f, 6.0f);

    RGBColor c2 = c0 + c1;
    EXPECT_FLOAT_EQ(5.0f, c2.r);
    EXPECT_FLOAT_EQ(7.0f, c2.g);
    EXPECT_FLOAT_EQ(9.0f, c2.b);

    c2 += c0;
    EXPECT_FLOAT_EQ(6.0f, c2.r);
    EXPECT_FLOAT_EQ(9.0f, c2.g);
    EXPECT_FLOAT_EQ(12.0f, c2.b);

    RGBColor c3 = c2 * 3.0f;
    EXPECT_FLOAT_EQ(18.0f, c3.r);
    EXPECT_FLOAT_EQ(27.0f, c3.g);
    EXPECT_FLOAT_EQ(36.0f, c3.b);

    c3 *= 2.0f;
    EXPECT_FLOAT_EQ(36.0f, c3.r);
    EXPECT_FLOAT_EQ(54.0f, c3.g);
    EXPECT_FLOAT_EQ(72.0f, c3.b);

    RGBColor c4 = c3 / 2.0f;
    EXPECT_FLOAT_EQ(18.0f, c4.r);
    EXPECT_FLOAT_EQ(27.0f, c4.g);
    EXPECT_FLOAT_EQ(36.0f, c4.b);

    c4 /= 3.0f;
    EXPECT_FLOAT_EQ(6.0f, c4.r);
    EXPECT_FLOAT_EQ(9.0f, c4.g);
    EXPECT_FLOAT_EQ(12.0f, c4.b);

    RGBColor c5 = c0 * c1;
    EXPECT_FLOAT_EQ(4.0f, c5.r);
    EXPECT_FLOAT_EQ(10.0f, c5.g);
    EXPECT_FLOAT_EQ(18.0f, c5.b);

    RGBColor c6(1.0f, 2.0f, 3.0f);
    EXPECT_TRUE(c0 == c6);
    RGBColor c7(2.0f, 2.0f, 3.0f);
    EXPECT_FALSE(c0 == c7);
    RGBColor c8(1.0f, 3.0f, 3.0f);
    EXPECT_FALSE(c0 == c8);
    RGBColor c9(1.0f, 2.0f, 4.0f);
    EXPECT_FALSE(c0 == c9);

    RGBColor c10 = c0.powc(2.0f);
    EXPECT_FLOAT_EQ(1.0f, c10.r);
    EXPECT_FLOAT_EQ(4.0f, c10.g);
    EXPECT_FLOAT_EQ(9.0f, c10.b);

    float c11 = c0.average();
    EXPECT_FLOAT_EQ(2.0, c11);

    // Non-member
    RGBColor c12 = 3.0f * c10;
    EXPECT_FLOAT_EQ(3.0f, c12.r);
    EXPECT_FLOAT_EQ(12.0f, c12.g);
    EXPECT_FLOAT_EQ(27.0f, c12.b);
}