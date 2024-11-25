[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![GoogleTest](https://github.com/mandyedi/raytracing-from-the-ground-up/workflows/GoogleTest/badge.svg)](https://github.com/mandyedi/raytracing-from-the-ground-up/actions)

The goal of this project is to make the sample project complete based on the book's chapters.

## Differences from the original source code
[Here is a list](https://github.com/mandyedi/raytracing-from-the-ground-up/blob/master/differences.md) of changes that I made in addition to implementing the missing chapters.

## Building the source code

You can use CMake to configure your build environment.
```shell
# In the repo root directory:
mkdir build
cd build
# Depending on your needs, build for debug or release: 
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake .. -DCMAKE_BUILD_TYPE=Release
# Depending on your OS type and installed development tools the development environment is set up in the build directory
```

## Unit testing

For testing, I am using GoogleTest. It is copied directly into the repo and can be found in the **third_party** directory.
Using CMake the test application is automatically added to the build environment.

## Source code origin

The source codes were downloaded from www raytracegroundup com (Note that this domain has expired and someone else bought it and uploaded some irrelevant content). Unfortunately, the original website is gone, you'll find something else on this link.  
I am keeping it here for reference in the **src_original** directory. The continued version can be found under the **src** directory.
