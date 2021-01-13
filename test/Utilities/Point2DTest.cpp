#include "gtest/gtest.h"
#include "../../src/Utilities/Point2D.h"

TEST(Point2DTest, Initialization) {
    Point2D p0;
    EXPECT_FLOAT_EQ(0.0f, p0.x);
    EXPECT_FLOAT_EQ(0.0f, p0.y);

    Point2D p1(1.0f);
    EXPECT_FLOAT_EQ(1.0f, p1.x);
    EXPECT_FLOAT_EQ(1.0f, p1.y);

    Point2D p2(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(1.0f, p2.x);
    EXPECT_FLOAT_EQ(2.0f, p2.y);

    Point2D p3(p2);
    EXPECT_FLOAT_EQ(1.0f, p3.x);
    EXPECT_FLOAT_EQ(2.0f, p3.y);

    p3 = p1;
    EXPECT_FLOAT_EQ(1.0f, p3.x);
    EXPECT_FLOAT_EQ(1.0f, p3.y);

    Point2D p4 = p3 * 3.0f;
    EXPECT_FLOAT_EQ(3.0f, p4.x);
    EXPECT_FLOAT_EQ(3.0f, p4.y);
}