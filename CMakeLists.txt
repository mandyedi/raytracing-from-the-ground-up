cmake_minimum_required (VERSION 3.1)

project (rtf VERSION 1.0
            DESCRIPTION "Ray Tracing from the Ground Up book example project"
            LANGUAGES CXX
)

if (MSVC)
  set(CMAKE_CXX_FLAGS "/EHsc /std:c++17")
  set(CMAKE_CXX_FLAGS_DEBUG "/Od")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else ()
  set(CMAKE_CXX_FLAGS "-std=c++17")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif ()

set (SOURCE_BRDFS
  src/BRDFs/BRDF.cpp
  src/BRDFs/BRDF.h
  src/BRDFs/GlossySpecular.cpp
  src/BRDFs/GlossySpecular.h
  src/BRDFs/Lambertian.cpp
  src/BRDFs/Lambertian.h
)

set (SOURCE_CAMERAS
  src/Cameras/Camera.cpp
  src/Cameras/Camera.h
  src/Cameras/FishEye.cpp
  src/Cameras/FishEye.h
  src/Cameras/Orthographic.cpp
  src/Cameras/Orthographic.h
  src/Cameras/Pinhole.cpp
  src/Cameras/Pinhole.h
  src/Cameras/Spherical.cpp
  src/Cameras/Spherical.h
  src/Cameras/StereoCamera.cpp
  src/Cameras/StereoCamera.h
  src/Cameras/ThinLens.cpp
  src/Cameras/ThinLens.h
)

set (SOURCE_GEOMETRICOBJECTS
  src/GeometricObjects/GeometricObject.cpp
  src/GeometricObjects/GeometricObject.h
  src/GeometricObjects/Instance.cpp
  src/GeometricObjects/Instance.h
)

set (SOURCE_BEVELED
  src/GeometricObjects/Beveled/BeveledBox.h
  src/GeometricObjects/Beveled/BeveledBox.cpp
)

set (SOURCE_COMPOUND
  src/GeometricObjects/Compound/Compound.cpp
  src/GeometricObjects/Compound/Compound.h
  src/GeometricObjects/Compound/CompoundSolidCylinder.cpp
  src/GeometricObjects/Compound/CompoundSolidCylinder.h
  src/GeometricObjects/Compound/Grid.cpp
  src/GeometricObjects/Compound/Grid.h
)

set (SOURCE_PARTOBJECTS
  src/GeometricObjects/PartObjects/ConvexPartCylinder.cpp
  src/GeometricObjects/PartObjects/ConvexPartCylinder.h
  src/GeometricObjects/PartObjects/ConvexPartSphere.cpp
  src/GeometricObjects/PartObjects/ConvexPartSphere.h
  src/GeometricObjects/PartObjects/ConvexPartTorus.cpp
  src/GeometricObjects/PartObjects/ConvexPartTorus.h
)

set (SOURCE_PRIMITIVES
  src/GeometricObjects/Primitives/Box.cpp
  src/GeometricObjects/Primitives/Box.h
  src/GeometricObjects/Primitives/Disk.cpp
  src/GeometricObjects/Primitives/Disk.h
  src/GeometricObjects/Primitives/OpenCylinder.cpp
  src/GeometricObjects/Primitives/OpenCylinder.h
  src/GeometricObjects/Primitives/Plane.cpp
  src/GeometricObjects/Primitives/Plane.h
  src/GeometricObjects/Primitives/Rectangle.cpp
  src/GeometricObjects/Primitives/Rectangle.h
  src/GeometricObjects/Primitives/Sphere.cpp
  src/GeometricObjects/Primitives/Sphere.h
  src/GeometricObjects/Primitives/Torus.cpp
  src/GeometricObjects/Primitives/Torus.h
)

set (SOURCE_TRIANGLES
  src/GeometricObjects/Triangles/Triangle.cpp
  src/GeometricObjects/Triangles/Triangle.h
)

set (SOURCE_LIGHTS
  src/Lights/Ambient.cpp
  src/Lights/Ambient.h
  src/Lights/AmbientOccluder.cpp
  src/Lights/AmbientOccluder.h
  src/Lights/AreaLight.cpp
  src/Lights/AreaLight.h
  src/Lights/Directional.cpp
  src/Lights/Directional.h
  src/Lights/EnvironmentLight.cpp
  src/Lights/EnvironmentLight.h
  src/Lights/Light.cpp
  src/Lights/Light.h
  src/Lights/PointLight.cpp
  src/Lights/PointLight.h
)

set (SOURCE_MATERIALS
  src/Materials/Emissive.cpp
  src/Materials/Emissive.h
  src/Materials/Material.cpp
  src/Materials/Material.h
  src/Materials/Matte.cpp
  src/Materials/Matte.h
  src/Materials/Phong.cpp
  src/Materials/Phong.h
)

set (SOURCE_SAMPLERS
  src/Samplers/Hammersley.cpp
  src/Samplers/Hammersley.h
  src/Samplers/Jittered.cpp
  src/Samplers/Jittered.h
  src/Samplers/MultiJittered.cpp
  src/Samplers/MultiJittered.h
  src/Samplers/NRooks.cpp
  src/Samplers/NRooks.h
  src/Samplers/PureRandom.cpp
  src/Samplers/PureRandom.h
  src/Samplers/Regular.cpp
  src/Samplers/Regular.h
  src/Samplers/Sampler.cpp
  src/Samplers/Sampler.h
)

set (SOURCE_SCENEBUILDERS
  src/SceneBuilders/BuildCh03PageOneImage.cpp
  src/SceneBuilders/BuildFigure03.18.cpp
  src/SceneBuilders/BuildFigure03.20.cpp
  src/SceneBuilders/BuildFigure04.04.cpp
)

set (SOURCE_TEXTURES
  src/Textures/Checker3D.cpp
  src/Textures/Checker3D.h
  src/Textures/Texture.cpp
  src/Textures/Texture.h
)

set (SOURCE_TRACERS
  src/Tracers/MultipleObjects.cpp
  src/Tracers/MultipleObjects.h
  src/Tracers/RayCast.cpp
  src/Tracers/RayCast.h
  src/Tracers/SingleSphere.cpp
  src/Tracers/SingleSphere.h
  src/Tracers/Tracer.cpp
  src/Tracers/Tracer.h
)

set (SOURCE_UTILITIES
  src/Utilities/BBox.cpp
  src/Utilities/BBox.h
  src/Utilities/Constants.h
  src/Utilities/Maths.h
  src/Utilities/Maths.cpp
  src/Utilities/Matrix.cpp
  src/Utilities/Matrix.h
  src/Utilities/Normal.cpp
  src/Utilities/Normal.h
  src/Utilities/Point2D.cpp
  src/Utilities/Point2D.h
  src/Utilities/Point3D.cpp
  src/Utilities/Point3D.h
  src/Utilities/Random.h
  src/Utilities/Ray.cpp
  src/Utilities/Ray.h
  src/Utilities/RGBColor.cpp
  src/Utilities/RGBColor.h
  src/Utilities/ShadeRec.cpp
  src/Utilities/ShadeRec.h
  src/Utilities/Vector3D.cpp
  src/Utilities/Vector3D.h
)

set (SOURCE_WORLD
  src/World/ViewPlane.cpp
  src/World/ViewPlane.h
  src/World/World.cpp
  src/World/World.h
)

source_group ("src/BRDFs" FILES ${SOURCE_BRDFS})
source_group ("src/Cameras" FILES ${SOURCE_CAMERAS})
source_group ("src/GeometricObjects" FILES ${SOURCE_GEOMETRICOBJECTS})
source_group ("src/GeometricObjects/Beveled" FILES ${SOURCE_BEVELED})
source_group ("src/GeometricObjects/Compound" FILES ${SOURCE_COMPOUND})
source_group ("src/GeometricObjects/PartObjects" FILES ${SOURCE_PARTOBJECTS})
source_group ("src/GeometricObjects/Primitives" FILES ${SOURCE_PRIMITIVES})
source_group ("src/GeometricObjects/Triangles" FILES ${SOURCE_TRIANGLES})
source_group ("src/Lights" FILES ${SOURCE_LIGHTS})
source_group ("src/Materials" FILES ${SOURCE_MATERIALS})
source_group ("src/Samplers" FILES ${SOURCE_SAMPLERS})
source_group ("src/SceneBuilders" FILES ${SOURCE_SCENEBUILDERS})
source_group ("src/Textures" FILES ${SOURCE_TEXTURES})
source_group ("src/Tracers" FILES ${SOURCE_TRACERS})
source_group ("src/Utilities" FILES ${SOURCE_UTILITIES})
source_group ("src/World" FILES ${SOURCE_WORLD})

add_library (libRTF STATIC
  ${SOURCE_BRDFS}
  ${SOURCE_CAMERAS}
  ${SOURCE_GEOMETRICOBJECTS}
  ${SOURCE_BEVELED}
  ${SOURCE_COMPOUND}
  ${SOURCE_PARTOBJECTS}
  ${SOURCE_PRIMITIVES}
  ${SOURCE_TRIANGLES}
  ${SOURCE_LIGHTS}
  ${SOURCE_MATERIALS}
  ${SOURCE_SAMPLERS}
  ${SOURCE_SCENEBUILDERS}
  ${SOURCE_TEXTURES}
  ${SOURCE_TRACERS}
  ${SOURCE_UTILITIES}
  ${SOURCE_WORLD}
)

add_executable (consoleApp consoleApp.cpp)

target_link_libraries (consoleApp libRTF)

# Unit Test Setup

set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing ()

add_subdirectory (third_party/googletest-release-1.10.0)

add_subdirectory (test)
