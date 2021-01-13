#include "gtest/gtest.h"
#include "../../src/Utilities/Point3D.h"

TEST(Point3DTest, Initialization) {
    Point3D p0;
    EXPECT_DOUBLE_EQ(0.0, p0.x);
    EXPECT_DOUBLE_EQ(0.0, p0.y);
    EXPECT_DOUBLE_EQ(0.0, p0.z);

    Point3D p1(1.0);
    EXPECT_DOUBLE_EQ(1.0, p1.x);
    EXPECT_DOUBLE_EQ(1.0, p1.y);
    EXPECT_DOUBLE_EQ(1.0, p1.z);

    Point3D p2(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(1.0, p2.x);
    EXPECT_DOUBLE_EQ(2.0, p2.y);
    EXPECT_DOUBLE_EQ(3.0, p2.z);

    Point3D p3(p2);
    EXPECT_DOUBLE_EQ(1.0, p3.x);
    EXPECT_DOUBLE_EQ(2.0, p3.y);
    EXPECT_DOUBLE_EQ(3.0, p3.z);

    p3 = p1;
    EXPECT_DOUBLE_EQ(1.0, p3.x);
    EXPECT_DOUBLE_EQ(1.0, p3.y);
    EXPECT_DOUBLE_EQ(1.0, p3.z);
}

TEST(Point3DTest, MathOperations) {
    Point3D p1(1.0);
    Point3D p2 = -p1;
    EXPECT_DOUBLE_EQ(-1.0, p2.x);
    EXPECT_DOUBLE_EQ(-1.0, p2.y);
    EXPECT_DOUBLE_EQ(-1.0, p2.z);

    Vector3D v0;
    v0 = v0 - p1;
    EXPECT_DOUBLE_EQ(-1.0, v0.x);
    EXPECT_DOUBLE_EQ(-1.0, v0.y);
    EXPECT_DOUBLE_EQ(-1.0, v0.z);

    Point3D p3 = p2 + v0;
    EXPECT_DOUBLE_EQ(-2.0, p3.x);
    EXPECT_DOUBLE_EQ(-2.0, p3.y);
    EXPECT_DOUBLE_EQ(-2.0, p3.z);

    Point3D p4 = p2 - v0;
    EXPECT_DOUBLE_EQ(0.0, p4.x);
    EXPECT_DOUBLE_EQ(0.0, p4.y);
    EXPECT_DOUBLE_EQ(0.0, p4.z);

    Point3D p5 = p3 * 3.0;
    EXPECT_DOUBLE_EQ(-6.0, p5.x);
    EXPECT_DOUBLE_EQ(-6.0, p5.y);
    EXPECT_DOUBLE_EQ(-6.0, p5.z);

    Point3D p6(3.0, 7.0, 12.0);
    Point3D p7(1.0, 3.0, 8.0);
    double d = p6.d_squared(p7);
    EXPECT_DOUBLE_EQ(36.0, d);

    double d2 = p6.distance(p7);
    EXPECT_DOUBLE_EQ(6.0, d2);
}

TEST(Point3DTest, MathOperationsNonMember) {
    Point3D p0(1.0, 2.0, 3.0);
    Point3D p1 = 3.0 * p0;
    EXPECT_DOUBLE_EQ(3.0, p1.x);
    EXPECT_DOUBLE_EQ(6.0, p1.y);
    EXPECT_DOUBLE_EQ(9.0, p1.z);

    Matrix m;
    m.m[0][0] = 1.0;
    m.m[0][1] = 2.0;
    m.m[0][2] = 3.0;
    m.m[0][3] = 4.0;

    m.m[1][0] = 5.0;
    m.m[1][1] = 6.0;
    m.m[1][2] = 7.0;
    m.m[1][3] = 8.0;

    m.m[2][0] = 9.0;
    m.m[2][1] = 10.0;
    m.m[2][2] = 11.0;
    m.m[2][3] = 12.0;

    Point3D p = m * p0;
    EXPECT_DOUBLE_EQ(18.0, p.x);
    EXPECT_DOUBLE_EQ(46.0, p.y);
    EXPECT_DOUBLE_EQ(74.0, p.z);
}