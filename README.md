[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![GoogleTest](https://github.com/mandyedi/raytracing-from-the-ground-up/workflows/GoogleTest/badge.svg)](https://github.com/mandyedi/raytracing-from-the-ground-up/actions)

<p align="center">
  <img width="300" height="300" src="https://raw.githubusercontent.com/mandyedi/raytracing-from-the-ground-up/master/src_original/chapters/Chapter28/Ray%20Traced%20Images%2028/Figure28.16.jpg">
</p>

The goal of this project is to make the sample project complete based on the book's chapters.

The origin of the project: [Raytracing from the Ground Up](http://www.raytracegroundup.com/)

### Differences from the original source code
[Here is a list](https://github.com/mandyedi/raytracing-from-the-ground-up/blob/master/differences.md) of changes that I made in addtition to implementing the mising chapters.

### Bulding the source code
You can use CMake to configure your build environment.
```shell
# In the repo root directory:
mkdir build
cd build
# Depending on your needs, build for debug or relese: 
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake .. -DCMAKE_BUILD_TYPE=Release
# Depending on your OS type and installed development tools the development environment is set up in the build directory
```

### Unit testing
For testing I am using GoogleTest. It is copied directly into the repo and can be found in the **third_party** directory.
Using CMake the test application is automatically added the build environment.

### Original source code
The original source codes are downloaded from the [official website](http://www.raytracegroundup.com/). I am keeping it here for refrence in the **src_original** directory. The continued version can be found under the **src** directory.
