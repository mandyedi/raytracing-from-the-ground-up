#include "gtest/gtest.h"
#include "../../src/Utilities/Ray.h"

TEST(RayTest, Initialization) {
    Ray r;
    EXPECT_FLOAT_EQ(0.0f, r.o.x);
    EXPECT_FLOAT_EQ(0.0f, r.o.y);
    EXPECT_FLOAT_EQ(0.0f, r.o.z);
    EXPECT_FLOAT_EQ(0.0f, r.d.x);
    EXPECT_FLOAT_EQ(0.0f, r.d.y);
    EXPECT_FLOAT_EQ(1.0f, r.d.z);

    Point3D o(1.0f, 2.0f, 3.0);
    Vector3D d(4.0f, 5.0f, 6.0);
    Ray r1(o, d);
    EXPECT_FLOAT_EQ(1.0f, r1.o.x);
    EXPECT_FLOAT_EQ(2.0f, r1.o.y);
    EXPECT_FLOAT_EQ(3.0f, r1.o.z);
    EXPECT_FLOAT_EQ(4.0f, r1.d.x);
    EXPECT_FLOAT_EQ(5.0f, r1.d.y);
    EXPECT_FLOAT_EQ(6.0f, r1.d.z);

    Ray r2(r1);
    EXPECT_FLOAT_EQ(1.0f, r2.o.x);
    EXPECT_FLOAT_EQ(2.0f, r2.o.y);
    EXPECT_FLOAT_EQ(3.0f, r2.o.z);
    EXPECT_FLOAT_EQ(4.0f, r2.d.x);
    EXPECT_FLOAT_EQ(5.0f, r2.d.y);
    EXPECT_FLOAT_EQ(6.0f, r2.d.z);

    Ray r3;
    r3 = r1;
    EXPECT_FLOAT_EQ(1.0f, r3.o.x);
    EXPECT_FLOAT_EQ(2.0f, r3.o.y);
    EXPECT_FLOAT_EQ(3.0f, r3.o.z);
    EXPECT_FLOAT_EQ(4.0f, r3.d.x);
    EXPECT_FLOAT_EQ(5.0f, r3.d.y);
    EXPECT_FLOAT_EQ(6.0f, r3.d.z);
}