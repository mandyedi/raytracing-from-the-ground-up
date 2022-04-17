#include <iostream>

#include "src/World/World.h"
#include "src/Cameras/Camera.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    std::cout << "Hello RT!\n";

    World *world = new World;
    world->build();
    world->render_figure_03_18();
    // world->camera_ptr->render_scene(*world);
    delete world;

    return 0;
}
