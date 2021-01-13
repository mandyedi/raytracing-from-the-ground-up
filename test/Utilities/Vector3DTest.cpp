#include "gtest/gtest.h"
#include "../../src/Utilities/Vector3D.h"
#include "../../src/Utilities/Normal.h"
#include "../../src/Utilities/Point3D.h"

TEST(Vector3DTest, Initialization) {
    Vector3D v0;
    EXPECT_DOUBLE_EQ(0.0, v0.x);
    EXPECT_DOUBLE_EQ(0.0, v0.y);
    EXPECT_DOUBLE_EQ(0.0, v0.z);

    Vector3D v1(1.0);
    EXPECT_DOUBLE_EQ(1.0, v1.x);
    EXPECT_DOUBLE_EQ(1.0, v1.y);
    EXPECT_DOUBLE_EQ(1.0, v1.z);

    Vector3D v2(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(1.0, v2.x);
    EXPECT_DOUBLE_EQ(2.0, v2.y);
    EXPECT_DOUBLE_EQ(3.0, v2.z);

    Vector3D v3(v2);
    EXPECT_DOUBLE_EQ(1.0, v3.x);
    EXPECT_DOUBLE_EQ(2.0, v3.y);
    EXPECT_DOUBLE_EQ(3.0, v3.z);

    Normal n(4.0, 5.0, 6.0);
    Vector3D v4(n);
    EXPECT_DOUBLE_EQ(4.0, v4.x);
    EXPECT_DOUBLE_EQ(5.0, v4.y);
    EXPECT_DOUBLE_EQ(6.0, v4.z);

    Point3D p(7.0, 8.0, 9.0);
    Vector3D v5(p);
    EXPECT_DOUBLE_EQ(7.0, v5.x);
    EXPECT_DOUBLE_EQ(8.0, v5.y);
    EXPECT_DOUBLE_EQ(9.0, v5.z);

    v0 = v3;
    EXPECT_DOUBLE_EQ(1.0, v0.x);
    EXPECT_DOUBLE_EQ(2.0, v0.y);
    EXPECT_DOUBLE_EQ(3.0, v0.z);

    v0 = n;
    EXPECT_DOUBLE_EQ(4.0, v0.x);
    EXPECT_DOUBLE_EQ(5.0, v0.y);
    EXPECT_DOUBLE_EQ(6.0, v0.z);

    v0 = p;
    EXPECT_DOUBLE_EQ(7.0, v0.x);
    EXPECT_DOUBLE_EQ(8.0, v0.y);
    EXPECT_DOUBLE_EQ(9.0, v0.z);
}

TEST(Vector3DTest, MathOperations) {
    Vector3D v0(7.0, 8.0, 9.0);
    Vector3D v2(1.0, 2.0, 3.0);

    v0 = -v0;
    EXPECT_DOUBLE_EQ(-7.0, v0.x);
    EXPECT_DOUBLE_EQ(-8.0, v0.y);
    EXPECT_DOUBLE_EQ(-9.0, v0.z);

    double length = v0.length();
    EXPECT_DOUBLE_EQ(13.92838827718412, length);

    double len_squared = v0.len_squared();
    EXPECT_DOUBLE_EQ(194.0, len_squared);

    Vector3D v6 = v0 * 3.0;
    EXPECT_DOUBLE_EQ(-21.0, v6.x);
    EXPECT_DOUBLE_EQ(-24.0, v6.y);
    EXPECT_DOUBLE_EQ(-27.0, v6.z);

    Vector3D v7 = v0 / 2.0;
    EXPECT_DOUBLE_EQ(-3.5, v7.x);
    EXPECT_DOUBLE_EQ(-4.0, v7.y);
    EXPECT_DOUBLE_EQ(-4.5, v7.z);

    Vector3D v8 = v0 + Vector3D(3.0, 1.0, 4.0);
    EXPECT_DOUBLE_EQ(-4.0, v8.x);
    EXPECT_DOUBLE_EQ(-7.0, v8.y);
    EXPECT_DOUBLE_EQ(-5.0, v8.z);

    v8 += v2;
    EXPECT_DOUBLE_EQ(-3.0, v8.x);
    EXPECT_DOUBLE_EQ(-5.0, v8.y);
    EXPECT_DOUBLE_EQ(-2.0, v8.z);

    Vector3D v9 = v8 - Vector3D(2.0, 5.0, 4.0);
    EXPECT_DOUBLE_EQ(-5.0, v9.x);
    EXPECT_DOUBLE_EQ(-10.0, v9.y);
    EXPECT_DOUBLE_EQ(-6.0, v9.z);

    double dot = v8 * v9;
    EXPECT_DOUBLE_EQ(77.0, dot);

    Vector3D x(1.0, 0.0, 0.0);
    Vector3D y(0.0, 1.0, 0.0);
    Vector3D z(0.0, 0.0, 1.0);

    Vector3D xy = x ^ y;
    EXPECT_DOUBLE_EQ(0.0, xy.x);
    EXPECT_DOUBLE_EQ(0.0, xy.y);
    EXPECT_DOUBLE_EQ(1.0, xy.z);

    Vector3D yz = y ^ z;
    EXPECT_DOUBLE_EQ(1.0, yz.x);
    EXPECT_DOUBLE_EQ(0.0, yz.y);
    EXPECT_DOUBLE_EQ(0.0, yz.z);

    Vector3D zx = z ^ x;
    EXPECT_DOUBLE_EQ(0.0, zx.x);
    EXPECT_DOUBLE_EQ(1.0, zx.y);
    EXPECT_DOUBLE_EQ(0.0, zx.z);

    Vector3D yx = y ^ x;
    EXPECT_DOUBLE_EQ(0.0, yx.x);
    EXPECT_DOUBLE_EQ(0.0, yx.y);
    EXPECT_DOUBLE_EQ(-1.0, yx.z);

    Vector3D zy = z ^ y;
    EXPECT_DOUBLE_EQ(-1.0, zy.x);
    EXPECT_DOUBLE_EQ(0.0, zy.y);
    EXPECT_DOUBLE_EQ(0.0, zy.z);

    Vector3D xz = x ^ z;
    EXPECT_DOUBLE_EQ(0.0, xz.x);
    EXPECT_DOUBLE_EQ(-1.0, xz.y);
    EXPECT_DOUBLE_EQ(0.0, xz.z);

    Vector3D xx = x ^ x;
    EXPECT_DOUBLE_EQ(0.0, xx.x);
    EXPECT_DOUBLE_EQ(0.0, xx.y);
    EXPECT_DOUBLE_EQ(0.0, xx.z);

    Vector3D yy = y ^ y;
    EXPECT_DOUBLE_EQ(0.0, yy.x);
    EXPECT_DOUBLE_EQ(0.0, yy.y);
    EXPECT_DOUBLE_EQ(0.0, yy.z);

    Vector3D zz = z ^ z;
    EXPECT_DOUBLE_EQ(0.0, zz.x);
    EXPECT_DOUBLE_EQ(0.0, zz.y);
    EXPECT_DOUBLE_EQ(0.0, zz.z);

    Vector3D norm(1.0);
    norm.normalize();
    EXPECT_DOUBLE_EQ(0.5773502691896258, norm.x);
    EXPECT_DOUBLE_EQ(0.5773502691896258, norm.y);
    EXPECT_DOUBLE_EQ(0.5773502691896258, norm.z);

    Vector3D v11(1.0);
    Vector3D hat = v11.hat();
    EXPECT_DOUBLE_EQ(0.5773502691896258, hat.x);
    EXPECT_DOUBLE_EQ(0.5773502691896258, hat.y);
    EXPECT_DOUBLE_EQ(0.5773502691896258, hat.z);
}

TEST(Vector3D, MathOperationsNonMember) {
    Vector3D v0 = 3.0 * Vector3D(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(3.0, v0.x);
    EXPECT_DOUBLE_EQ(6.0, v0.y);
    EXPECT_DOUBLE_EQ(9.0, v0.z);

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

    Vector3D v1 = m * v0;
    EXPECT_DOUBLE_EQ(42.0, v1.x);
    EXPECT_DOUBLE_EQ(114.0, v1.y);
    EXPECT_DOUBLE_EQ(186, v1.z);
}