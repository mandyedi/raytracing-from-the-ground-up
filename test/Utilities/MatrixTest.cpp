#include "gtest/gtest.h"
#include "../../src/Utilities/Matrix.h"

class MatrixTest : public testing::Test {
protected:
    void SetUp() override {
        m0.m[0][0] = 0.0f;
        m0.m[0][1] = 1.0f;
        m0.m[0][2] = 2.0f;
        m0.m[0][3] = 3.0f;
        m0.m[1][0] = 0.0f;
        m0.m[1][1] = 1.0f;
        m0.m[1][2] = 2.0f;
        m0.m[1][3] = 3.0f;
        m0.m[2][0] = 0.0f;
        m0.m[2][1] = 1.0f;
        m0.m[2][2] = 2.0f;
        m0.m[2][3] = 3.0f;
        m0.m[3][0] = 0.0f;
        m0.m[3][1] = 1.0f;
        m0.m[3][2] = 2.0f;
        m0.m[3][3] = 3.0f;

        m1.m[0][0] = 0.0f;
        m1.m[0][1] = 1.0f;
        m1.m[0][2] = 2.0f;
        m1.m[0][3] = 3.0f;
        m1.m[1][0] = 0.0f;
        m1.m[1][1] = 1.0f;
        m1.m[1][2] = 2.0f;
        m1.m[1][3] = 3.0f;
        m1.m[2][0] = 0.0f;
        m1.m[2][1] = 1.0f;
        m1.m[2][2] = 2.0f;
        m1.m[2][3] = 3.0f;
        m1.m[3][0] = 0.0f;
        m1.m[3][1] = 1.0f;
        m1.m[3][2] = 2.0f;
        m1.m[3][3] = 3.0f;
    }

    // virtual void TearDown() {
    // }

    Matrix i;
    Matrix m0;
    Matrix m1;
};

TEST_F(MatrixTest, Initialization) {
    // Default constructor
    EXPECT_FLOAT_EQ(1.0f, i.m[0][0]);
    EXPECT_FLOAT_EQ(0.0f, i.m[0][1]);
    EXPECT_FLOAT_EQ(0.0f, i.m[0][2]);
    EXPECT_FLOAT_EQ(0.0f, i.m[0][3]);
    EXPECT_FLOAT_EQ(0.0f, i.m[1][0]);
    EXPECT_FLOAT_EQ(1.0f, i.m[1][1]);
    EXPECT_FLOAT_EQ(0.0f, i.m[1][2]);
    EXPECT_FLOAT_EQ(0.0f, i.m[1][3]);
    EXPECT_FLOAT_EQ(0.0f, i.m[2][0]);
    EXPECT_FLOAT_EQ(0.0f, i.m[2][1]);
    EXPECT_FLOAT_EQ(1.0f, i.m[2][2]);
    EXPECT_FLOAT_EQ(0.0f, i.m[2][3]);
    EXPECT_FLOAT_EQ(0.0f, i.m[3][0]);
    EXPECT_FLOAT_EQ(0.0f, i.m[3][1]);
    EXPECT_FLOAT_EQ(0.0f, i.m[3][2]);
    EXPECT_FLOAT_EQ(1.0f, i.m[3][3]);

    Matrix mc(m0);
    EXPECT_FLOAT_EQ(0.0f, mc.m[0][0]);
    EXPECT_FLOAT_EQ(1.0f, mc.m[0][1]);
    EXPECT_FLOAT_EQ(2.0f, mc.m[0][2]);
    EXPECT_FLOAT_EQ(3.0f, mc.m[0][3]);
    EXPECT_FLOAT_EQ(0.0f, mc.m[1][0]);
    EXPECT_FLOAT_EQ(1.0f, mc.m[1][1]);
    EXPECT_FLOAT_EQ(2.0f, mc.m[1][2]);
    EXPECT_FLOAT_EQ(3.0f, mc.m[1][3]);
    EXPECT_FLOAT_EQ(0.0f, mc.m[2][0]);
    EXPECT_FLOAT_EQ(1.0f, mc.m[2][1]);
    EXPECT_FLOAT_EQ(2.0f, mc.m[2][2]);
    EXPECT_FLOAT_EQ(3.0f, mc.m[2][3]);
    EXPECT_FLOAT_EQ(0.0f, mc.m[3][0]);
    EXPECT_FLOAT_EQ(1.0f, mc.m[3][1]);
    EXPECT_FLOAT_EQ(2.0f, mc.m[3][2]);
    EXPECT_FLOAT_EQ(3.0f, mc.m[3][3]);

    Matrix ma = m0;
    EXPECT_FLOAT_EQ(0.0f, ma.m[0][0]);
    EXPECT_FLOAT_EQ(1.0f, ma.m[0][1]);
    EXPECT_FLOAT_EQ(2.0f, ma.m[0][2]);
    EXPECT_FLOAT_EQ(3.0f, ma.m[0][3]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[1][0]);
    EXPECT_FLOAT_EQ(1.0f, ma.m[1][1]);
    EXPECT_FLOAT_EQ(2.0f, ma.m[1][2]);
    EXPECT_FLOAT_EQ(3.0f, ma.m[1][3]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[2][0]);
    EXPECT_FLOAT_EQ(1.0f, ma.m[2][1]);
    EXPECT_FLOAT_EQ(2.0f, ma.m[2][2]);
    EXPECT_FLOAT_EQ(3.0f, ma.m[2][3]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[3][0]);
    EXPECT_FLOAT_EQ(1.0f, ma.m[3][1]);
    EXPECT_FLOAT_EQ(2.0f, ma.m[3][2]);
    EXPECT_FLOAT_EQ(3.0f, ma.m[3][3]);

    ma.set_identity();
    EXPECT_FLOAT_EQ(1.0f, ma.m[0][0]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[0][1]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[0][2]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[0][3]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[1][0]);
    EXPECT_FLOAT_EQ(1.0f, ma.m[1][1]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[1][2]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[1][3]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[2][0]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[2][1]);
    EXPECT_FLOAT_EQ(1.0f, ma.m[2][2]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[2][3]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[3][0]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[3][1]);
    EXPECT_FLOAT_EQ(0.0f, ma.m[3][2]);
    EXPECT_FLOAT_EQ(1.0f, ma.m[3][3]);
}

TEST_F(MatrixTest, MathOperations) {
    Matrix mMul = m0 * m1;
    EXPECT_FLOAT_EQ(0.0f, mMul.m[0][0]);
    EXPECT_FLOAT_EQ(6.0f, mMul.m[0][1]);
    EXPECT_FLOAT_EQ(12.0f, mMul.m[0][2]);
    EXPECT_FLOAT_EQ(18.0f, mMul.m[0][3]);
    EXPECT_FLOAT_EQ(0.0f, mMul.m[1][0]);
    EXPECT_FLOAT_EQ(6.0f, mMul.m[1][1]);
    EXPECT_FLOAT_EQ(12.0f, mMul.m[1][2]);
    EXPECT_FLOAT_EQ(18.0f, mMul.m[1][3]);
    EXPECT_FLOAT_EQ(0.0f, mMul.m[2][0]);
    EXPECT_FLOAT_EQ(6.0f, mMul.m[2][1]);
    EXPECT_FLOAT_EQ(12.0f, mMul.m[2][2]);
    EXPECT_FLOAT_EQ(18.0f, mMul.m[2][3]);
    EXPECT_FLOAT_EQ(0.0f, mMul.m[3][0]);
    EXPECT_FLOAT_EQ(6.0f, mMul.m[3][1]);
    EXPECT_FLOAT_EQ(12.0f, mMul.m[3][2]);
    EXPECT_FLOAT_EQ(18.0f, mMul.m[3][3]);

    Matrix mDiv = mMul / 2.0f;
    EXPECT_FLOAT_EQ(0.0f, mDiv.m[0][0]);
    EXPECT_FLOAT_EQ(3.0f, mDiv.m[0][1]);
    EXPECT_FLOAT_EQ(6.0f, mDiv.m[0][2]);
    EXPECT_FLOAT_EQ(9.0f, mDiv.m[0][3]);
    EXPECT_FLOAT_EQ(0.0f, mDiv.m[1][0]);
    EXPECT_FLOAT_EQ(3.0f, mDiv.m[1][1]);
    EXPECT_FLOAT_EQ(6.0f, mDiv.m[1][2]);
    EXPECT_FLOAT_EQ(9.0f, mDiv.m[1][3]);
    EXPECT_FLOAT_EQ(0.0f, mDiv.m[2][0]);
    EXPECT_FLOAT_EQ(3.0f, mDiv.m[2][1]);
    EXPECT_FLOAT_EQ(6.0f, mDiv.m[2][2]);
    EXPECT_FLOAT_EQ(9.0f, mDiv.m[2][3]);
    EXPECT_FLOAT_EQ(0.0f, mDiv.m[3][0]);
    EXPECT_FLOAT_EQ(3.0f, mDiv.m[3][1]);
    EXPECT_FLOAT_EQ(6.0f, mDiv.m[3][2]);
    EXPECT_FLOAT_EQ(9.0f, mDiv.m[3][3]);
}