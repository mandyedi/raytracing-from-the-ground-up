#include "gtest/gtest.h"
#include "../../src/Utilities/Matrix.h"

class MatrixTest : public testing::Test {
protected:
    void SetUp() override {
        m0.m[0][0] = 0.0;
        m0.m[0][1] = 1.0;
        m0.m[0][2] = 2.0;
        m0.m[0][3] = 3.0;
        m0.m[1][0] = 0.0;
        m0.m[1][1] = 1.0;
        m0.m[1][2] = 2.0;
        m0.m[1][3] = 3.0;
        m0.m[2][0] = 0.0;
        m0.m[2][1] = 1.0;
        m0.m[2][2] = 2.0;
        m0.m[2][3] = 3.0;
        m0.m[3][0] = 0.0;
        m0.m[3][1] = 1.0;
        m0.m[3][2] = 2.0;
        m0.m[3][3] = 3.0;

        m1.m[0][0] = 0.0;
        m1.m[0][1] = 1.0;
        m1.m[0][2] = 2.0;
        m1.m[0][3] = 3.0;
        m1.m[1][0] = 0.0;
        m1.m[1][1] = 1.0;
        m1.m[1][2] = 2.0;
        m1.m[1][3] = 3.0;
        m1.m[2][0] = 0.0;
        m1.m[2][1] = 1.0;
        m1.m[2][2] = 2.0;
        m1.m[2][3] = 3.0;
        m1.m[3][0] = 0.0;
        m1.m[3][1] = 1.0;
        m1.m[3][2] = 2.0;
        m1.m[3][3] = 3.0;
    }

    // virtual void TearDown() {
    // }

    Matrix i;
    Matrix m0;
    Matrix m1;
};

TEST_F(MatrixTest, Initialization) {
    // Default constructor
    EXPECT_DOUBLE_EQ(1.0, i.m[0][0]);
    EXPECT_DOUBLE_EQ(0.0, i.m[0][1]);
    EXPECT_DOUBLE_EQ(0.0, i.m[0][2]);
    EXPECT_DOUBLE_EQ(0.0, i.m[0][3]);
    EXPECT_DOUBLE_EQ(0.0, i.m[1][0]);
    EXPECT_DOUBLE_EQ(1.0, i.m[1][1]);
    EXPECT_DOUBLE_EQ(0.0, i.m[1][2]);
    EXPECT_DOUBLE_EQ(0.0, i.m[1][3]);
    EXPECT_DOUBLE_EQ(0.0, i.m[2][0]);
    EXPECT_DOUBLE_EQ(0.0, i.m[2][1]);
    EXPECT_DOUBLE_EQ(1.0, i.m[2][2]);
    EXPECT_DOUBLE_EQ(0.0, i.m[2][3]);
    EXPECT_DOUBLE_EQ(0.0, i.m[3][0]);
    EXPECT_DOUBLE_EQ(0.0, i.m[3][1]);
    EXPECT_DOUBLE_EQ(0.0, i.m[3][2]);
    EXPECT_DOUBLE_EQ(1.0, i.m[3][3]);

    Matrix mc(m0);
    EXPECT_DOUBLE_EQ(0.0, mc.m[0][0]);
    EXPECT_DOUBLE_EQ(1.0, mc.m[0][1]);
    EXPECT_DOUBLE_EQ(2.0, mc.m[0][2]);
    EXPECT_DOUBLE_EQ(3.0, mc.m[0][3]);
    EXPECT_DOUBLE_EQ(0.0, mc.m[1][0]);
    EXPECT_DOUBLE_EQ(1.0, mc.m[1][1]);
    EXPECT_DOUBLE_EQ(2.0, mc.m[1][2]);
    EXPECT_DOUBLE_EQ(3.0, mc.m[1][3]);
    EXPECT_DOUBLE_EQ(0.0, mc.m[2][0]);
    EXPECT_DOUBLE_EQ(1.0, mc.m[2][1]);
    EXPECT_DOUBLE_EQ(2.0, mc.m[2][2]);
    EXPECT_DOUBLE_EQ(3.0, mc.m[2][3]);
    EXPECT_DOUBLE_EQ(0.0, mc.m[3][0]);
    EXPECT_DOUBLE_EQ(1.0, mc.m[3][1]);
    EXPECT_DOUBLE_EQ(2.0, mc.m[3][2]);
    EXPECT_DOUBLE_EQ(3.0, mc.m[3][3]);

    Matrix ma = m0;
    EXPECT_DOUBLE_EQ(0.0, ma.m[0][0]);
    EXPECT_DOUBLE_EQ(1.0, ma.m[0][1]);
    EXPECT_DOUBLE_EQ(2.0, ma.m[0][2]);
    EXPECT_DOUBLE_EQ(3.0, ma.m[0][3]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[1][0]);
    EXPECT_DOUBLE_EQ(1.0, ma.m[1][1]);
    EXPECT_DOUBLE_EQ(2.0, ma.m[1][2]);
    EXPECT_DOUBLE_EQ(3.0, ma.m[1][3]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[2][0]);
    EXPECT_DOUBLE_EQ(1.0, ma.m[2][1]);
    EXPECT_DOUBLE_EQ(2.0, ma.m[2][2]);
    EXPECT_DOUBLE_EQ(3.0, ma.m[2][3]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[3][0]);
    EXPECT_DOUBLE_EQ(1.0, ma.m[3][1]);
    EXPECT_DOUBLE_EQ(2.0, ma.m[3][2]);
    EXPECT_DOUBLE_EQ(3.0, ma.m[3][3]);

    ma.set_identity();
    EXPECT_DOUBLE_EQ(1.0, ma.m[0][0]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[0][1]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[0][2]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[0][3]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[1][0]);
    EXPECT_DOUBLE_EQ(1.0, ma.m[1][1]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[1][2]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[1][3]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[2][0]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[2][1]);
    EXPECT_DOUBLE_EQ(1.0, ma.m[2][2]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[2][3]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[3][0]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[3][1]);
    EXPECT_DOUBLE_EQ(0.0, ma.m[3][2]);
    EXPECT_DOUBLE_EQ(1.0, ma.m[3][3]);
}

TEST_F(MatrixTest, MathOperations) {
    Matrix mMul = m0 * m1;
    EXPECT_DOUBLE_EQ(0.0, mMul.m[0][0]);
    EXPECT_DOUBLE_EQ(6.0, mMul.m[0][1]);
    EXPECT_DOUBLE_EQ(12.0, mMul.m[0][2]);
    EXPECT_DOUBLE_EQ(18.0, mMul.m[0][3]);
    EXPECT_DOUBLE_EQ(0.0, mMul.m[1][0]);
    EXPECT_DOUBLE_EQ(6.0, mMul.m[1][1]);
    EXPECT_DOUBLE_EQ(12.0, mMul.m[1][2]);
    EXPECT_DOUBLE_EQ(18.0, mMul.m[1][3]);
    EXPECT_DOUBLE_EQ(0.0, mMul.m[2][0]);
    EXPECT_DOUBLE_EQ(6.0, mMul.m[2][1]);
    EXPECT_DOUBLE_EQ(12.0, mMul.m[2][2]);
    EXPECT_DOUBLE_EQ(18.0, mMul.m[2][3]);
    EXPECT_DOUBLE_EQ(0.0, mMul.m[3][0]);
    EXPECT_DOUBLE_EQ(6.0, mMul.m[3][1]);
    EXPECT_DOUBLE_EQ(12.0, mMul.m[3][2]);
    EXPECT_DOUBLE_EQ(18.0, mMul.m[3][3]);

    Matrix mDiv = mMul / 2.0;
    EXPECT_DOUBLE_EQ(0.0, mDiv.m[0][0]);
    EXPECT_DOUBLE_EQ(3.0, mDiv.m[0][1]);
    EXPECT_DOUBLE_EQ(6.0, mDiv.m[0][2]);
    EXPECT_DOUBLE_EQ(9.0, mDiv.m[0][3]);
    EXPECT_DOUBLE_EQ(0.0, mDiv.m[1][0]);
    EXPECT_DOUBLE_EQ(3.0, mDiv.m[1][1]);
    EXPECT_DOUBLE_EQ(6.0, mDiv.m[1][2]);
    EXPECT_DOUBLE_EQ(9.0, mDiv.m[1][3]);
    EXPECT_DOUBLE_EQ(0.0, mDiv.m[2][0]);
    EXPECT_DOUBLE_EQ(3.0, mDiv.m[2][1]);
    EXPECT_DOUBLE_EQ(6.0, mDiv.m[2][2]);
    EXPECT_DOUBLE_EQ(9.0, mDiv.m[2][3]);
    EXPECT_DOUBLE_EQ(0.0, mDiv.m[3][0]);
    EXPECT_DOUBLE_EQ(3.0, mDiv.m[3][1]);
    EXPECT_DOUBLE_EQ(6.0, mDiv.m[3][2]);
    EXPECT_DOUBLE_EQ(9.0, mDiv.m[3][3]);
}