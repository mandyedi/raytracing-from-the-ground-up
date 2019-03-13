CXX		  := g++
# TODO(fix): add -Wall and fix all warnings
#CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb
CXX_FLAGS := -std=c++17 -ggdb
WX_FLAGS  := -D_FILE_OFFSET_BITS=64 -D__WXGTK__

BIN		:= bin
LIB		:= lib
WX_LIB	:= -lgthread-2.0 -pthread -lX11 -lXxf86vm -lSM -lgtk-3 -lgdk-3 -lpangocairo-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lXtst -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfontconfig -lfreetype -lwxtiff-3.1 -lwxjpeg-3.1 -lwxregexu-3.1 -lwxscintilla-3.1 -lexpat -lpng -lz -ldl -lm
WX_STATIC	:= \
	/usr/local/lib/libwx_gtk3u_xrc-3.1.a \
	/usr/local/lib/libwx_gtk3u_qa-3.1.a \
	/usr/local/lib/libwx_baseu_net-3.1.a \
	/usr/local/lib/libwx_gtk3u_html-3.1.a \
	/usr/local/lib/libwx_gtk3u_core-3.1.a \
	/usr/local/lib/libwx_baseu_xml-3.1.a \
	/usr/local/lib/libwx_baseu-3.1.a

LIBRARIES	:=
EXECUTABLE	:= wxraytracer

INCLUDE	:= -I/usr/local/lib/wx/include/gtk3-unicode-static-3.1 \
			-I/usr/local/include/wx-3.1 \
			-Isrc \
			-Isrc/BRDFs \
			-Isrc/Cameras \
			-Isrc/GeometricObjects \
			-Isrc/Lights \
			-Isrc/Materials \
			-Isrc/Tracers \
			-Isrc/UserInterface \
			-Isrc/Utilities \
			-Isrc/World

SRC		:= src/BRDFs/BRDF.cpp \
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
			src/UserInterface/wxraytracer.cpp \
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

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) $(WX_FLAGS) -L$(LIB) $^ -o $@ $(WX_STATIC) $(LIBRARIES) $(WX_LIB)

clean:
	-rm -rf $(BIN)/*
