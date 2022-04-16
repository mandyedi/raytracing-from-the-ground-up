#include "gtest/gtest.h"
#include "../../src/Utilities/Normal.h"
// #include "Vector3D.h"
// #include "Point3D.h"

class NormalTest : public testing::Test {
protected:
    void SetUp() override {
        n1.x = 0.0f;
        n1.y = 1.0f;
        n1.z = 2.0f;

        n2.x = 0.0f;
        n2.y = 1.0f;
        n2.z = 2.0f;

        v1.x = 0.0f;
        v1.y = 1.0f;
        v1.z = 2.0f;

        p1.x = 0.0f;
        p1.y = 1.0f;
        p1.z = 2.0f;
    }

    Normal n0;
    Normal n1;
    Normal n2;
    Vector3D v1;
    Point3D p1;
};

TEST_F(NormalTest, Initialization) {
    EXPECT_FLOAT_EQ(0.0f, n0.x);
    EXPECT_FLOAT_EQ(0.0f, n0.y);
    EXPECT_FLOAT_EQ(0.0f, n0.z);

    Normal single(1.0);
    EXPECT_FLOAT_EQ(1.0f, single.x);
    EXPECT_FLOAT_EQ(1.0f, single.y);
    EXPECT_FLOAT_EQ(1.0f, single.z);

    Normal all(1.0f, 2.0f, 3.0);
    EXPECT_FLOAT_EQ(1.0f, all.x);
    EXPECT_FLOAT_EQ(2.0f, all.y);
    EXPECT_FLOAT_EQ(3.0f, all.z);

    Normal nCopy(n1);
    EXPECT_FLOAT_EQ(0.0f, nCopy.x);
    EXPECT_FLOAT_EQ(1.0f, nCopy.y);
    EXPECT_FLOAT_EQ(2.0f, nCopy.z);

    Normal nAssign = n1;
    EXPECT_FLOAT_EQ(0.0f, nAssign.x);
    EXPECT_FLOAT_EQ(1.0f, nAssign.y);
    EXPECT_FLOAT_EQ(2.0f, nAssign.z);

    Normal vCopy(v1);
    EXPECT_FLOAT_EQ(0.0f, vCopy.x);
    EXPECT_FLOAT_EQ(1.0f, vCopy.y);
    EXPECT_FLOAT_EQ(2.0f, vCopy.z);

    Normal vAssign;
    vAssign = v1;
    EXPECT_FLOAT_EQ(0.0f, vAssign.x);
    EXPECT_FLOAT_EQ(1.0f, vAssign.y);
    EXPECT_FLOAT_EQ(2.0f, vAssign.z);

    Normal pAssign;
    pAssign = p1;
    EXPECT_FLOAT_EQ(0.0f, pAssign.x);
    EXPECT_FLOAT_EQ(1.0f, pAssign.y);
    EXPECT_FLOAT_EQ(2.0f, pAssign.z);
}

TEST_F(NormalTest, MathOperations) {
    Normal u = -n1;
    EXPECT_FLOAT_EQ(-0.0f, u.x);
    EXPECT_FLOAT_EQ(-1.0f, u.y);
    EXPECT_FLOAT_EQ(-2.0f, u.z);

    Normal a = n1 + n2;
    EXPECT_FLOAT_EQ(0.0f, a.x);
    EXPECT_FLOAT_EQ(2.0f, a.y);
    EXPECT_FLOAT_EQ(4.0f, a.z);

    a += n1;
    EXPECT_FLOAT_EQ(0.0f, a.x);
    EXPECT_FLOAT_EQ(3.0f, a.y);
    EXPECT_FLOAT_EQ(6.0f, a.z);

    double m = a * v1;
    EXPECT_FLOAT_EQ(15.0f, m);

    Normal m2 = a * 3.0f;
    EXPECT_FLOAT_EQ(0.0f, m2.x);
    EXPECT_FLOAT_EQ(9.0f, m2.y);
    EXPECT_FLOAT_EQ(18.0f, m2.z);

    Normal norm(1.0);
    norm.normalize();
    EXPECT_FLOAT_EQ(0.5773502691896258, norm.x);
    EXPECT_FLOAT_EQ(0.5773502691896258, norm.y);
    EXPECT_FLOAT_EQ(0.5773502691896258, norm.z);
}

TEST_F(NormalTest, MathOperationsNonMember) {
    Normal m = 3.0 * n1;
    EXPECT_FLOAT_EQ(0.0f, m.x);
    EXPECT_FLOAT_EQ(3.0f, m.y);
    EXPECT_FLOAT_EQ(6.0f, m.z);

    Vector3D addVN = v1 + n1;
    EXPECT_FLOAT_EQ(0.0f, addVN.x);
    EXPECT_FLOAT_EQ(2.0f, addVN.y);
    EXPECT_FLOAT_EQ(4.0f, addVN.z);

    Vector3D subVN = v1 - n1;
    EXPECT_FLOAT_EQ(0.0f, subVN.x);
    EXPECT_FLOAT_EQ(0.0f, subVN.y);
    EXPECT_FLOAT_EQ(0.0f, subVN.z);

    double dot = v1 * n1;
    EXPECT_FLOAT_EQ(5.0f, dot);

    Matrix m0;
    m0.m[0][0] = 1.0f;
    m0.m[0][1] = 2.0f;
    m0.m[0][2] = 3.0f;

    m0.m[1][0] = 1.0f;
    m0.m[1][1] = 2.0f;
    m0.m[1][2] = 3.0f;

    m0.m[2][0] = 1.0f;
    m0.m[2][1] = 2.0f;
    m0.m[2][2] = 3.0f;

    Normal t = m0 * n1;
    EXPECT_FLOAT_EQ(3.0f, t.x);
    EXPECT_FLOAT_EQ(6.0f, t.y);
    EXPECT_FLOAT_EQ(9.0f, t.z);
}