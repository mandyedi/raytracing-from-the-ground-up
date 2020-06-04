CXX		  := g++
# TODO(fix): add -Wall -Wextra and fix all warnings
CXX_FLAGS := -std=c++17 -ggdb -O0

BIN			:= bin
LIB			:= lib
EXECUTABLE	:= raytracer

INCLUDE	:=	-Isrc \
			-Isrc/BRDFs \
			-Isrc/Cameras \
			-Isrc/GeometricObjects \
			-Isrc/Lights \
			-Isrc/Materials \
			-Isrc/Tracers \
			-Isrc/Utilities \
			-Isrc/World

SRC		:= src/consoleApp.cpp \
			src/BRDFs/BRDF.cpp \
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

all: $(BIN)/$(EXECUTABLE)

build: clean all

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC) | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -L$(LIB) $^ -o $(BIN)/$(EXECUTABLE)

clean:
	-rm -rf $(BIN)/*
