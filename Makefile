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
RayTracer: main.o Scene.o Point.o Vector.o Sample.o Sampler.o Color.o Ray.o Film.o Camera.o Scene.h Point.h Vector.h Sample.h Sampler.h Color.h Ray.h Film.h Camera.h
	$(CC) $(CFLAGS) -o RayTracer main.o Scene.o Point.o Vector.o Sample.o Sampler.o Color.o Ray.o Film.o Camera.o $(INCFLAGS) $(LDFLAGS)
main.o: main.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
Scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Scene.cpp
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

clean:
	$(RM) *.o RayTracer *.png
