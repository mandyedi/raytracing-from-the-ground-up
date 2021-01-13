#include "gtest/gtest.h"
#include "../../src/Utilities/Normal.h"
// #include "Vector3D.h"
// #include "Point3D.h"

class NormalTest : public testing::Test {
protected:
    void SetUp() override {
        n1.x = 0.0;
        n1.y = 1.0;
        n1.z = 2.0;

        n2.x = 0.0;
        n2.y = 1.0;
        n2.z = 2.0;

        v1.x = 0.0;
        v1.y = 1.0;
        v1.z = 2.0;

        p1.x = 0.0;
        p1.y = 1.0;
        p1.z = 2.0;
    }

    Normal n0;
    Normal n1;
    Normal n2;
    Vector3D v1;
    Point3D p1;
};

TEST_F(NormalTest, Initialization) {
    EXPECT_DOUBLE_EQ(0.0, n0.x);
    EXPECT_DOUBLE_EQ(0.0, n0.y);
    EXPECT_DOUBLE_EQ(0.0, n0.z);

    Normal single(1.0);
    EXPECT_DOUBLE_EQ(1.0, single.x);
    EXPECT_DOUBLE_EQ(1.0, single.y);
    EXPECT_DOUBLE_EQ(1.0, single.z);

    Normal all(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(1.0, all.x);
    EXPECT_DOUBLE_EQ(2.0, all.y);
    EXPECT_DOUBLE_EQ(3.0, all.z);

    Normal nCopy(n1);
    EXPECT_DOUBLE_EQ(0.0, nCopy.x);
    EXPECT_DOUBLE_EQ(1.0, nCopy.y);
    EXPECT_DOUBLE_EQ(2.0, nCopy.z);

    Normal nAssign = n1;
    EXPECT_DOUBLE_EQ(0.0, nAssign.x);
    EXPECT_DOUBLE_EQ(1.0, nAssign.y);
    EXPECT_DOUBLE_EQ(2.0, nAssign.z);

    Normal vCopy(v1);
    EXPECT_DOUBLE_EQ(0.0, vCopy.x);
    EXPECT_DOUBLE_EQ(1.0, vCopy.y);
    EXPECT_DOUBLE_EQ(2.0, vCopy.z);

    Normal vAssign;
    vAssign = v1;
    EXPECT_DOUBLE_EQ(0.0, vAssign.x);
    EXPECT_DOUBLE_EQ(1.0, vAssign.y);
    EXPECT_DOUBLE_EQ(2.0, vAssign.z);

    Normal pAssign;
    pAssign = p1;
    EXPECT_DOUBLE_EQ(0.0, pAssign.x);
    EXPECT_DOUBLE_EQ(1.0, pAssign.y);
    EXPECT_DOUBLE_EQ(2.0, pAssign.z);
}

TEST_F(NormalTest, MathOperations) {
    Normal u = -n1;
    EXPECT_DOUBLE_EQ(-0.0, u.x);
    EXPECT_DOUBLE_EQ(-1.0, u.y);
    EXPECT_DOUBLE_EQ(-2.0, u.z);

    Normal a = n1 + n2;
    EXPECT_DOUBLE_EQ(0.0, a.x);
    EXPECT_DOUBLE_EQ(2.0, a.y);
    EXPECT_DOUBLE_EQ(4.0, a.z);

    a += n1;
    EXPECT_DOUBLE_EQ(0.0, a.x);
    EXPECT_DOUBLE_EQ(3.0, a.y);
    EXPECT_DOUBLE_EQ(6.0, a.z);

    double m = a * v1;
    EXPECT_DOUBLE_EQ(15.0, m);

    Normal m2 = a * 3.0;
    EXPECT_DOUBLE_EQ(0.0, m2.x);
    EXPECT_DOUBLE_EQ(9.0, m2.y);
    EXPECT_DOUBLE_EQ(18.0, m2.z);

    Normal norm(1.0);
    norm.normalize();
    EXPECT_DOUBLE_EQ(0.5773502691896258, norm.x);
    EXPECT_DOUBLE_EQ(0.5773502691896258, norm.y);
    EXPECT_DOUBLE_EQ(0.5773502691896258, norm.z);
}

TEST_F(NormalTest, MathOperationsNonMember) {
    Normal m = 3.0 * n1;
    EXPECT_DOUBLE_EQ(0.0, m.x);
    EXPECT_DOUBLE_EQ(3.0, m.y);
    EXPECT_DOUBLE_EQ(6.0, m.z);

    Vector3D addVN = v1 + n1;
    EXPECT_DOUBLE_EQ(0.0, addVN.x);
    EXPECT_DOUBLE_EQ(2.0, addVN.y);
    EXPECT_DOUBLE_EQ(4.0, addVN.z);

    Vector3D subVN = v1 - n1;
    EXPECT_DOUBLE_EQ(0.0, subVN.x);
    EXPECT_DOUBLE_EQ(0.0, subVN.y);
    EXPECT_DOUBLE_EQ(0.0, subVN.z);

    double dot = v1 * n1;
    EXPECT_DOUBLE_EQ(5.0, dot);

    Matrix m0;
    m0.m[0][0] = 1.0;
    m0.m[0][1] = 2.0;
    m0.m[0][2] = 3.0;

    m0.m[1][0] = 1.0;
    m0.m[1][1] = 2.0;
    m0.m[1][2] = 3.0;

    m0.m[2][0] = 1.0;
    m0.m[2][1] = 2.0;
    m0.m[2][2] = 3.0;

    Normal t = m0 * n1;
    EXPECT_DOUBLE_EQ(3.0, t.x);
    EXPECT_DOUBLE_EQ(6.0, t.y);
    EXPECT_DOUBLE_EQ(9.0, t.z);
}