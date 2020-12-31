#include "gtest/gtest.h"
#include "Plane.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "World.h"

TEST(PlaneTest, RayIntersection) {
	Ray ray({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f});
	Plane plane({0.0f, 0.0f, -3.0f}, {0.0f, 0.0f, 1.0f});
	World world;
	double t = 1.0E10;
	ShadeRec shadeRec(world);
	bool isHit = plane.hit(ray, t, shadeRec);
	EXPECT_TRUE(isHit);
	EXPECT_DOUBLE_EQ(shadeRec.normal.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.y, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.normal.z, 1.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.x, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.y, 0.0f);
	EXPECT_DOUBLE_EQ(shadeRec.local_hit_point.z, -3.0f);
}

TEST(PlaneTest, NoIntersection) {
	// Ray direction is opposite to palne normal
	Ray ray({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
	Plane plane({0.0f, 0.0f, -3.0f}, {0.0f, 0.0f, 1.0f});
	World world;
	double t = 1.0E10;
	ShadeRec shadeRec(world);
	bool isHit = plane.hit(ray, t, shadeRec);
	EXPECT_FALSE(isHit);

	// Ray plane are parallel
	t = 1.0E10;
	Ray ray2({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
	isHit = plane.hit(ray, t, shadeRec);
	EXPECT_FALSE(isHit);
}