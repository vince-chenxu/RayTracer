CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED -DOSX -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses
INCFLAGS = -I./glm-0.9.7.1 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -g -DGL_GLEXT_PROTOTYPES
INCFLAGS = -I./glm-0.9.7.1 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L./lib/nix/ \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lGLEW -lglut -lGLU -lGL -lX11 -lfreeimage
endif

RM = /bin/rm -f
all: RayTracer
RayTracer: main.o Scene.o Point.o Vector.o Sample.o Sampler.o Color.o Ray.o Film.o Camera.o Vertex.o Tri.o Sph.o Triangle.o Sphere.o Normal.o LocalGeo.o Shape.o Intersection.o BRDF.o RayTracer.o Matrix.o Transformation.o Primitive.o GeometricPrimitive.o Material.o AggregatePrimitive.o Light.o PointLight.o DirectionalLight.o Scene.h Point.h Vector.h Sample.h Sampler.h Color.h Ray.h Film.h Camera.h Vertex.h Tri.h Sph.h Triangle.h Sphere.h Normal.h LocalGeo.h Shape.h Intersection.h BRDF.h RayTracer.h Matrix.h Transformation.h Primitive.h GeometricPrimitive.h Material.h AggregatePrimitive.h Light.h PointLight.h DirectionalLight.h
	$(CC) $(CFLAGS) -o RayTracer main.o Scene.o Point.o Vector.o Sample.o Sampler.o Color.o Ray.o Film.o Camera.o Vertex.o Tri.o Sph.o Triangle.o Sphere.o Normal.o LocalGeo.o Shape.o Intersection.o BRDF.o RayTracer.o Matrix.o Transformation.o Primitive.o GeometricPrimitive.o Material.o AggregatePrimitive.o Light.o PointLight.o DirectionalLight.o $(INCFLAGS) $(LDFLAGS)
main.o: main.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c -O3 -funroll-loops main.cpp
Scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c -O3 -funroll-loops Scene.cpp
Point.o: Point.cpp Point.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Point.cpp
Vector.o: Vector.cpp Vector.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Vector.cpp
Sample.o: Sample.cpp Sample.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sample.cpp
Sampler.o: Sampler.cpp Sampler.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sampler.cpp
Color.o: Color.cpp Color.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Color.cpp
Ray.o: Ray.cpp Ray.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Ray.cpp
Film.o: Film.cpp Film.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Film.cpp
Camera.o: Camera.cpp Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Camera.cpp
Vertex.o: Vertex.cpp Vertex.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Vertex.cpp
Tri.o: Tri.cpp Tri.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Tri.cpp
Sph.o: Sph.cpp Sph.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sph.cpp
Triangle.o: Triangle.cpp Triangle.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Triangle.cpp
Sphere.o: Sphere.cpp Sphere.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sphere.cpp
Normal.o: Normal.cpp Normal.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Normal.cpp
LocalGeo.o: LocalGeo.cpp LocalGeo.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c LocalGeo.cpp
Shape.o: Shape.cpp Shape.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Shape.cpp
Intersection.o: Intersection.cpp Intersection.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Intersection.cpp
BRDF.o: BRDF.cpp BRDF.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c BRDF.cpp
RayTracer.o: RayTracer.cpp RayTracer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c RayTracer.cpp
Matrix.o: Matrix.cpp Matrix.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Matrix.cpp
Transformation.o: Transformation.cpp Transformation.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transformation.cpp
Primitive.o: Primitive.cpp Primitive.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Primitive.cpp
GeometricPrimitive.o: GeometricPrimitive.cpp GeometricPrimitive.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c GeometricPrimitive.cpp
Material.o: Material.cpp Material.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Material.cpp
AggregatePrimitive.o: AggregatePrimitive.cpp AggregatePrimitive.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c AggregatePrimitive.cpp
Light.o: Light.cpp Light.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Light.cpp
PointLight.o: PointLight.cpp PointLight.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c PointLight.cpp
DirectionalLight.o: DirectionalLight.cpp DirectionalLight.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c DirectionalLight.cpp

clean:
	$(RM) *.o RayTracer *.png
