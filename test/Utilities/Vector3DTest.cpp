#include "gtest/gtest.h"
#include "../../src/Utilities/Vector3D.h"
#include "../../src/Utilities/Normal.h"
#include "../../src/Utilities/Point3D.h"

TEST(Vector3DTest, Initialization) {
    Vector3D v0;
    EXPECT_FLOAT_EQ(0.0f, v0.x);
    EXPECT_FLOAT_EQ(0.0f, v0.y);
    EXPECT_FLOAT_EQ(0.0f, v0.z);

    Vector3D v1(1.0);
    EXPECT_FLOAT_EQ(1.0f, v1.x);
    EXPECT_FLOAT_EQ(1.0f, v1.y);
    EXPECT_FLOAT_EQ(1.0f, v1.z);

    Vector3D v2(1.0f, 2.0f, 3.0);
    EXPECT_FLOAT_EQ(1.0f, v2.x);
    EXPECT_FLOAT_EQ(2.0f, v2.y);
    EXPECT_FLOAT_EQ(3.0f, v2.z);

    Vector3D v3(v2);
    EXPECT_FLOAT_EQ(1.0f, v3.x);
    EXPECT_FLOAT_EQ(2.0f, v3.y);
    EXPECT_FLOAT_EQ(3.0f, v3.z);

    Normal n(4.0f, 5.0f, 6.0);
    Vector3D v4(n);
    EXPECT_FLOAT_EQ(4.0f, v4.x);
    EXPECT_FLOAT_EQ(5.0f, v4.y);
    EXPECT_FLOAT_EQ(6.0f, v4.z);

    Point3D p(7.0f, 8.0f, 9.0);
    Vector3D v5(p);
    EXPECT_FLOAT_EQ(7.0f, v5.x);
    EXPECT_FLOAT_EQ(8.0f, v5.y);
    EXPECT_FLOAT_EQ(9.0f, v5.z);

    v0 = v3;
    EXPECT_FLOAT_EQ(1.0f, v0.x);
    EXPECT_FLOAT_EQ(2.0f, v0.y);
    EXPECT_FLOAT_EQ(3.0f, v0.z);

    v0 = n;
    EXPECT_FLOAT_EQ(4.0f, v0.x);
    EXPECT_FLOAT_EQ(5.0f, v0.y);
    EXPECT_FLOAT_EQ(6.0f, v0.z);

    v0 = p;
    EXPECT_FLOAT_EQ(7.0f, v0.x);
    EXPECT_FLOAT_EQ(8.0f, v0.y);
    EXPECT_FLOAT_EQ(9.0f, v0.z);
}

TEST(Vector3DTest, MathOperations) {
    Vector3D v0(7.0f, 8.0f, 9.0);
    Vector3D v2(1.0f, 2.0f, 3.0);

    v0 = -v0;
    EXPECT_FLOAT_EQ(-7.0f, v0.x);
    EXPECT_FLOAT_EQ(-8.0f, v0.y);
    EXPECT_FLOAT_EQ(-9.0f, v0.z);

    double length = v0.length();
    EXPECT_FLOAT_EQ(13.92838827718412, length);

    double len_squared = v0.len_squared();
    EXPECT_FLOAT_EQ(194.0f, len_squared);

    Vector3D v6 = v0 * 3.0f;
    EXPECT_FLOAT_EQ(-21.0f, v6.x);
    EXPECT_FLOAT_EQ(-24.0f, v6.y);
    EXPECT_FLOAT_EQ(-27.0f, v6.z);

    Vector3D v7 = v0 / 2.0f;
    EXPECT_FLOAT_EQ(-3.5, v7.x);
    EXPECT_FLOAT_EQ(-4.0f, v7.y);
    EXPECT_FLOAT_EQ(-4.5, v7.z);

    Vector3D v8 = v0 + Vector3D(3.0f, 1.0f, 4.0);
    EXPECT_FLOAT_EQ(-4.0f, v8.x);
    EXPECT_FLOAT_EQ(-7.0f, v8.y);
    EXPECT_FLOAT_EQ(-5.0f, v8.z);

    v8 += v2;
    EXPECT_FLOAT_EQ(-3.0f, v8.x);
    EXPECT_FLOAT_EQ(-5.0f, v8.y);
    EXPECT_FLOAT_EQ(-2.0f, v8.z);

    Vector3D v9 = v8 - Vector3D(2.0f, 5.0f, 4.0);
    EXPECT_FLOAT_EQ(-5.0f, v9.x);
    EXPECT_FLOAT_EQ(-10.0f, v9.y);
    EXPECT_FLOAT_EQ(-6.0f, v9.z);

    double dot = v8 * v9;
    EXPECT_FLOAT_EQ(77.0f, dot);

    Vector3D x(1.0f, 0.0f, 0.0);
    Vector3D y(0.0f, 1.0f, 0.0);
    Vector3D z(0.0f, 0.0f, 1.0);

    Vector3D xy = x ^ y;
    EXPECT_FLOAT_EQ(0.0f, xy.x);
    EXPECT_FLOAT_EQ(0.0f, xy.y);
    EXPECT_FLOAT_EQ(1.0f, xy.z);

    Vector3D yz = y ^ z;
    EXPECT_FLOAT_EQ(1.0f, yz.x);
    EXPECT_FLOAT_EQ(0.0f, yz.y);
    EXPECT_FLOAT_EQ(0.0f, yz.z);

    Vector3D zx = z ^ x;
    EXPECT_FLOAT_EQ(0.0f, zx.x);
    EXPECT_FLOAT_EQ(1.0f, zx.y);
    EXPECT_FLOAT_EQ(0.0f, zx.z);

    Vector3D yx = y ^ x;
    EXPECT_FLOAT_EQ(0.0f, yx.x);
    EXPECT_FLOAT_EQ(0.0f, yx.y);
    EXPECT_FLOAT_EQ(-1.0f, yx.z);

    Vector3D zy = z ^ y;
    EXPECT_FLOAT_EQ(-1.0f, zy.x);
    EXPECT_FLOAT_EQ(0.0f, zy.y);
    EXPECT_FLOAT_EQ(0.0f, zy.z);

    Vector3D xz = x ^ z;
    EXPECT_FLOAT_EQ(0.0f, xz.x);
    EXPECT_FLOAT_EQ(-1.0f, xz.y);
    EXPECT_FLOAT_EQ(0.0f, xz.z);

    Vector3D xx = x ^ x;
    EXPECT_FLOAT_EQ(0.0f, xx.x);
    EXPECT_FLOAT_EQ(0.0f, xx.y);
    EXPECT_FLOAT_EQ(0.0f, xx.z);

    Vector3D yy = y ^ y;
    EXPECT_FLOAT_EQ(0.0f, yy.x);
    EXPECT_FLOAT_EQ(0.0f, yy.y);
    EXPECT_FLOAT_EQ(0.0f, yy.z);

    Vector3D zz = z ^ z;
    EXPECT_FLOAT_EQ(0.0f, zz.x);
    EXPECT_FLOAT_EQ(0.0f, zz.y);
    EXPECT_FLOAT_EQ(0.0f, zz.z);

    Vector3D norm(1.0);
    norm.normalize();
    EXPECT_FLOAT_EQ(0.5773502691896258, norm.x);
    EXPECT_FLOAT_EQ(0.5773502691896258, norm.y);
    EXPECT_FLOAT_EQ(0.5773502691896258, norm.z);

    Vector3D v11(1.0);
    Vector3D hat = v11.hat();
    EXPECT_FLOAT_EQ(0.5773502691896258, hat.x);
    EXPECT_FLOAT_EQ(0.5773502691896258, hat.y);
    EXPECT_FLOAT_EQ(0.5773502691896258, hat.z);
}

TEST(Vector3D, MathOperationsNonMember) {
    Vector3D v0 = 3.0 * Vector3D(1.0f, 2.0f, 3.0);
    EXPECT_FLOAT_EQ(3.0f, v0.x);
    EXPECT_FLOAT_EQ(6.0f, v0.y);
    EXPECT_FLOAT_EQ(9.0f, v0.z);

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

    Vector3D v1 = m * v0;
    EXPECT_FLOAT_EQ(42.0f, v1.x);
    EXPECT_FLOAT_EQ(114.0f, v1.y);
    EXPECT_FLOAT_EQ(186, v1.z);
}