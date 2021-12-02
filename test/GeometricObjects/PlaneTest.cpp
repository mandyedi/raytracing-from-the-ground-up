#include "gtest/gtest.h"
#include "../../src/GeometricObjects/Plane.h"
#include "../../src/Utilities/Ray.h"
#include "../../src/Utilities/ShadeRec.h"
#include "../../src/World/World.h"

TEST(PlaneTest, RayIntersection) {
	Ray ray(Point3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, -1.0));
	Plane plane(Point3D(0.0, 0.0, -3.0), Normal(0.0, 0.0, 1.0));
	World *world = new World;
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
	delete world;
}

TEST(PlaneTest, NoIntersection) {
	// Ray direction is opposite to palne normal
	Ray ray(Point3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 1.0f));
	Plane plane(Point3D(0.0f, 0.0f, -3.0f), Normal(0.0f, 0.0f, 1.0f));
	World *world = new World;
	double t = 1.0E10;
	ShadeRec shadeRec(world);
	bool isHit = plane.hit(ray, t, shadeRec);
	EXPECT_FALSE(isHit);

	// Ray plane are parallel
	t = 1.0E10;
	Ray ray2(Point3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f));
	isHit = plane.hit(ray, t, shadeRec);
	EXPECT_FALSE(isHit);

	delete world;
}