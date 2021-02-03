# Differences
Here is a list of changes that makes the code more consistent or easier to use.  
I do not present small changes like extending Utilities/Maths.h max(double x0, double x1); function with a version that accepts float arguments too.

## World::build() Method
For most of the chapters there is an example scene that you can render. These scenes and the related components (camera, tracer, geometric objects, etc.) are set up in a build method of the class World.  
To keep it simple and well organized I declare bulid methods for every chapter in World.h and implement the definitions in separate build*.cpp files.  
Each build methods have a unique name and contains the chapters number too. For example for "Chapter 3.6.5 The build Function" the declaration is:
```cpp
World::build_single_sphere_3_6_5();
```

## CMake
I am not supporting any IDE, rather I provide a CMake configuration file so you can code and build with your favorite IDE.

## Unit Tests
Used framework: GoogleTest

## Comments Remowal
I removed all the unnecesary comments. Though this project is for beginners it should be teach also good practices about commenting.  
Number rule one for commenting: explain the "why", not the "how".  
Here are some realy bad/unnecessary comments to avoid:
```cpp
Camera(); // default constructor

// ----------- set_eye
inline void
Camera::set_eye(const Point3D& p) {
    eye = p;
}
```

## wxWidgets
Currently I do not find it important to have a UI so I removed the wxWidgets dependancy. Since the book concentrate on the source code, math and optics, I believe a simple console application is enough for the present.  
Later I might put wxWidgets back or maybe some other UI framweork.

## Color Consts
Frequently used colors (black, white, red, etc.) are defined in RGBColor.h and can be used as below.  
```cpp
RGBColor b = RGBColor::black;
```

## Render Stereo Method
In chapter 12.5 Implementation (Stereoscopy) there is a separate function called Pinhole::render_stereo(World& w, float, int offset). I found it simpler to just extend the original Camera::render_scene method with the x and offset arguments.
