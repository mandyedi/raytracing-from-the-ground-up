#include <iostream>

#include "src/World/World.h"
#include "src/Cameras/Camera.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    std::cout << "Hello RT!\n";

    World *world = new World;
    world->build();
    // world->render_scene(); // Use this for Chapter 3 renderings
    world->camera_ptr->render_scene(*world);
    delete world;

    return 0;
}
