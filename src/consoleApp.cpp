#include <iostream>

#include "World.h"
#include "RayCast.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello RT!\n";

    World *world = new World;
    
    world->build_shaded_objects();
    world->camera_ptr->render_scene(*world);

    delete world;

    return 0;
}