#include "gtest/gtest.h"
#include "../../src/GeometricObjects/Sphere.h"
#include "../../src/Utilities/Ray.h"
#include "../../src/Utilities/ShadeRec.h"
#include "../../src/World/World.h"

TEST(SphereeTest, RayIntersection) {
	// [Figure 3.7, ray 2] One hit point
	Ray ray({0.0f, 3.0f, 6.0f}, {0.0f, 0.0f, -1.0f});
	Sphere sphere({0.0f, 0.0f, 0.0f}, 3.0);
	World world;
	ShadeRec shadeRec(world);
	double t = 1.0E10;
	bool isHit = sphere.hit(ray, t, shadeRec);
	EXPECT_TRUE(isHit);
	EXPECT_DOUBLE_EQ(shadeRec.normal.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.y, 1.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.z, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.y, 3.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.z, 0.0f);

	// [Figure 3.7, ray 3] Two hit points
	Ray ray2({0.0f, 0.0f, 6.0f}, {0.0f, 0.0f, -1.0f});
	t = 1.0E10;
	isHit = sphere.hit(ray2, t, shadeRec);
	EXPECT_TRUE(isHit);
	EXPECT_DOUBLE_EQ(shadeRec.normal.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.y, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.z, 1.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.y, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.z, 3.0f);

	// [Figure 3.8, ray 3]
	Ray ray3({0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f});
	t = 1.0E10;
	isHit = sphere.hit(ray3, t, shadeRec);
	EXPECT_TRUE(isHit);
	EXPECT_DOUBLE_EQ(shadeRec.normal.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.y, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.z, -1.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.y, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.z, -3.0f);

	// [Figure 3.8, ray 4]
	Ray ray4({0.0f, 0.0f, 3.0f}, {0.0f, 0.0f, -1.0f});
	t = 1.0E10;
	isHit = sphere.hit(ray4, t, shadeRec);
	EXPECT_TRUE(isHit);
	EXPECT_DOUBLE_EQ(shadeRec.normal.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.y, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.z, -1.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.y, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.z, -3.0f);
}

TEST(SphereeTest, NoIntersection) {
	// [Figure 3.7, ray 1]
	Ray ray({0.0f, 4.0f, 6.0f}, {0.0f, 0.0f, -1.0f});
	Sphere sphere({0.0f, 0.0f, 0.0f}, 3.0);
	World world;
	double t = 1.0E10;
	ShadeRec shadeRec(world);
	bool isHit = sphere.hit(ray, t, shadeRec);
	EXPECT_FALSE(isHit);

	// [Figure 3.8, ray 1]
	Ray ray2({0.0f, 2.0f, -3.0f}, {0.0f, 0.0f, -1.0f});
	t = 1.0E10;
	isHit = sphere.hit(ray2, t, shadeRec);
	EXPECT_FALSE(isHit);

	// [Figure 3.8, ray 2]
	Ray ray3({0.0f, 0.0f, -3.0f}, {0.0f, 0.0f, -1.0f});
	t = 1.0E10;
	isHit = sphere.hit(ray3, t, shadeRec);
	EXPECT_FALSE(isHit);
}