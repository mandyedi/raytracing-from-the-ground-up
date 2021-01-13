#include "gtest/gtest.h"
#include "../../src/Utilities/Ray.h"

TEST(RayTest, Initialization) {
    Ray r;
    EXPECT_DOUBLE_EQ(0.0, r.o.x);
    EXPECT_DOUBLE_EQ(0.0, r.o.y);
    EXPECT_DOUBLE_EQ(0.0, r.o.z);
    EXPECT_DOUBLE_EQ(0.0, r.d.x);
    EXPECT_DOUBLE_EQ(0.0, r.d.y);
    EXPECT_DOUBLE_EQ(1.0, r.d.z);

    Point3D o(1.0, 2.0, 3.0);
    Vector3D d(4.0, 5.0, 6.0);
    Ray r1(o, d);
    EXPECT_DOUBLE_EQ(1.0, r1.o.x);
    EXPECT_DOUBLE_EQ(2.0, r1.o.y);
    EXPECT_DOUBLE_EQ(3.0, r1.o.z);
    EXPECT_DOUBLE_EQ(4.0, r1.d.x);
    EXPECT_DOUBLE_EQ(5.0, r1.d.y);
    EXPECT_DOUBLE_EQ(6.0, r1.d.z);

    Ray r2(r1);
    EXPECT_DOUBLE_EQ(1.0, r2.o.x);
    EXPECT_DOUBLE_EQ(2.0, r2.o.y);
    EXPECT_DOUBLE_EQ(3.0, r2.o.z);
    EXPECT_DOUBLE_EQ(4.0, r2.d.x);
    EXPECT_DOUBLE_EQ(5.0, r2.d.y);
    EXPECT_DOUBLE_EQ(6.0, r2.d.z);

    Ray r3;
    r3 = r1;
    EXPECT_DOUBLE_EQ(1.0, r3.o.x);
    EXPECT_DOUBLE_EQ(2.0, r3.o.y);
    EXPECT_DOUBLE_EQ(3.0, r3.o.z);
    EXPECT_DOUBLE_EQ(4.0, r3.d.x);
    EXPECT_DOUBLE_EQ(5.0, r3.d.y);
    EXPECT_DOUBLE_EQ(6.0, r3.d.z);
}