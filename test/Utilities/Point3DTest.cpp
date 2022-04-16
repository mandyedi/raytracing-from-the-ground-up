#include "gtest/gtest.h"
#include "../../src/Utilities/Point3D.h"

TEST(Point3DTest, Initialization) {
    Point3D p0;
    EXPECT_FLOAT_EQ(0.0f, p0.x);
    EXPECT_FLOAT_EQ(0.0f, p0.y);
    EXPECT_FLOAT_EQ(0.0f, p0.z);

    Point3D p1(1.0);
    EXPECT_FLOAT_EQ(1.0f, p1.x);
    EXPECT_FLOAT_EQ(1.0f, p1.y);
    EXPECT_FLOAT_EQ(1.0f, p1.z);

    Point3D p2(1.0f, 2.0f, 3.0);
    EXPECT_FLOAT_EQ(1.0f, p2.x);
    EXPECT_FLOAT_EQ(2.0f, p2.y);
    EXPECT_FLOAT_EQ(3.0f, p2.z);

    Point3D p3(p2);
    EXPECT_FLOAT_EQ(1.0f, p3.x);
    EXPECT_FLOAT_EQ(2.0f, p3.y);
    EXPECT_FLOAT_EQ(3.0f, p3.z);

    p3 = p1;
    EXPECT_FLOAT_EQ(1.0f, p3.x);
    EXPECT_FLOAT_EQ(1.0f, p3.y);
    EXPECT_FLOAT_EQ(1.0f, p3.z);
}

TEST(Point3DTest, MathOperations) {
    Point3D p1(1.0);
    Point3D p2 = -p1;
    EXPECT_FLOAT_EQ(-1.0f, p2.x);
    EXPECT_FLOAT_EQ(-1.0f, p2.y);
    EXPECT_FLOAT_EQ(-1.0f, p2.z);

    Vector3D v0(2.0f, 2.0f, 2.0f);
    v0 = p1 - v0;
    EXPECT_FLOAT_EQ(-1.0f, v0.x);
    EXPECT_FLOAT_EQ(-1.0f, v0.y);
    EXPECT_FLOAT_EQ(-1.0f, v0.z);

    Point3D p3 = p2 + v0;
    EXPECT_FLOAT_EQ(-2.0f, p3.x);
    EXPECT_FLOAT_EQ(-2.0f, p3.y);
    EXPECT_FLOAT_EQ(-2.0f, p3.z);

    Point3D p4 = p2 - v0;
    EXPECT_FLOAT_EQ(0.0f, p4.x);
    EXPECT_FLOAT_EQ(0.0f, p4.y);
    EXPECT_FLOAT_EQ(0.0f, p4.z);

    Point3D p5 = p3 * 3.0f;
    EXPECT_FLOAT_EQ(-6.0f, p5.x);
    EXPECT_FLOAT_EQ(-6.0f, p5.y);
    EXPECT_FLOAT_EQ(-6.0f, p5.z);

    Point3D p6(3.0f, 7.0f, 12.0);
    Point3D p7(1.0f, 3.0f, 8.0);
    double d = p6.d_squared(p7);
    EXPECT_FLOAT_EQ(36.0f, d);

    double d2 = p6.distance(p7);
    EXPECT_FLOAT_EQ(6.0f, d2);
}

TEST(Point3DTest, MathOperationsNonMember) {
    Point3D p0(1.0f, 2.0f, 3.0);
    Point3D p1 = 3.0 * p0;
    EXPECT_FLOAT_EQ(3.0f, p1.x);
    EXPECT_FLOAT_EQ(6.0f, p1.y);
    EXPECT_FLOAT_EQ(9.0f, p1.z);

    Matrix m;
    m.m[0][0] = 1.0f;
    m.m[0][1] = 2.0f;
    m.m[0][2] = 3.0f;
    m.m[0][3] = 4.0f;

    m.m[1][0] = 5.0f;
    m.m[1][1] = 6.0f;
    m.m[1][2] = 7.0f;
    m.m[1][3] = 8.0f;

    m.m[2][0] = 9.0f;
    m.m[2][1] = 10.0f;
    m.m[2][2] = 11.0f;
    m.m[2][3] = 12.0f;

    Point3D p = m * p0;
    EXPECT_FLOAT_EQ(18.0f, p.x);
    EXPECT_FLOAT_EQ(46.0f, p.y);
    EXPECT_FLOAT_EQ(74.0f, p.z);
}