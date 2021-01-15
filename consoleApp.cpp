#include <iostream>

#include "src/World/World.h"
#include "src/Tracers/RayCast.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    std::cout << "Hello RT!\n";

    // Chapter 3.6 A Bare-Bones Ray Tracer
    //World *world = new World;
    //world->build_single_sphere_3_6_5();
    //world->render_single_sphere_3_6_5();
    //delete world;

    // Chapter 3.9 Ray Tracing Multiple Objects
    World *world = new World;
    world->build_multiple_objects_3_9();
    world->render_multiple_objects_3_9();
    delete world;

    return 0;
}