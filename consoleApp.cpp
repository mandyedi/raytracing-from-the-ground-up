#include <iostream>

#include "src/World/World.h"
#include "src/Tracers/RayCast.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    std::cout << "Hello RT!\n";

    // Chapter 3.6 A Bare-Bones Ray Tracer
    World *world = new World;
    world->build_single_sphere_3_6_5();
    world->render_single_sphere_3_6_5();
    delete world;

    return 0;
}