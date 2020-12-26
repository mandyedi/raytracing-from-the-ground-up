CXX		  := g++
CXX_FLAGS := -std=c++17 -ggdb -O0 -Wall -Wextra

BIN			:= bin
LIB			:= lib
EXECUTABLE	:= raytracer
TEST        := gtest

INCLUDE	:=	-Isrc \
			-Isrc/BRDFs \
			-Isrc/Cameras \
			-Isrc/GeometricObjects \
			-Isrc/Lights \
			-Isrc/Materials \
			-Isrc/Tracers \
			-Isrc/Utilities \
			-Isrc/World

SRC		:=  src/BRDFs/BRDF.cpp \
			src/BRDFs/Lambertian.cpp \
			src/Cameras/Camera.cpp \
			src/Cameras/Pinhole.cpp \
			src/GeometricObjects/GeometricObject.cpp \
			src/GeometricObjects/Plane.cpp \
			src/GeometricObjects/Sphere.cpp \
			src/Lights/Ambient.cpp \
			src/Lights/Directional.cpp \
			src/Lights/Light.cpp \
			src/Materials/Material.cpp \
			src/Materials/Matte.cpp \
			src/Tracers/MultipleObjects.cpp \
			src/Tracers/RayCast.cpp \
			src/Tracers/SingleSphere.cpp \
			src/Tracers/Tracer.cpp \
			src/Utilities/Matrix.cpp \
			src/Utilities/Normal.cpp \
			src/Utilities/Point2D.cpp \
			src/Utilities/Point3D.cpp \
			src/Utilities/Ray.cpp \
			src/Utilities/RGBColor.cpp \
			src/Utilities/ShadeRec.cpp \
			src/Utilities/Vector3D.cpp \
			src/World/ViewPlane.cpp \
			src/World/World.cpp

SRC_GTEST	:= test/main.cpp \
				test/Utilities/MathsTest.cpp \
				test/Utilities/MatrixTest.cpp \
				test/Utilities/NormalTest.cpp \
				test/Utilities/Point2DTest.cpp \
				test/Utilities/Point3DTest.cpp \
				test/Utilities/RayTest.cpp \
				test/Utilities/RGBColorTest.cpp \
				test/Utilities/Vector3DTest.cpp

# Build and run google test

run-test: clean $(BIN)/$(TEST)
	$(BIN)/$(TEST)

$(BIN)/$(TEST): $(SRC_GTEST) $(SRC) | $(BIN)
	# works if -lgtest -lpthread are at the end of the line 
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -Ithirdparty/googletest-v1.10.0/include -Lthirdparty/googletest-v1.10.0/lib $^ -o $(BIN)/$(TEST) -lgtest -lpthread

# Build and run raytracer

build: clean $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): src/consoleApp.cpp $(SRC) | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -L$(LIB) $^ -o $(BIN)/$(EXECUTABLE)

# Common stuff
clean:
	-rm -rf $(BIN)/*
