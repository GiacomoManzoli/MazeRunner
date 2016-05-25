# Makefile for OpenGL flight simulator
# ------------------------------------

# Object files list
#OBJS = flightsim.o plane.o vector_operations.o
OBJS = textureBMP.o maze_object.o tnt.o block.o maze.o main.o
# Executable name
EXENAME = a.out

# Macros
CC = g++
CCOPTS = -c -g -O0 -Wall -Wno-deprecated
LINK = g++
LINKOPTS = -o

all : $(EXENAME)

# Testing for OS X v Linux
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
     LIBS = -framework GLUT -framework OpenGL -framework Cocoa
else
     LIBS = -lGL -lGLU -lglut
endif

# The compiling step
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS) $(LIBS)

# Object files
main.o : main.cpp
	$(CC) $(CCOPTS) main.cpp
block.o : block.cpp block.h
	$(CC) $(CCOPTS) block.cpp
tnt.o : tnt.cpp tnt.h
	$(CC) $(CCOPTS) tnt.cpp
maze.o : maze.cpp maze.h
	$(CC) $(CCOPTS) maze.cpp
mazeObject.o : maze_object.cpp maze_object.h
	$(CC) $(CCOPTS) maze_object.cpp
textureBMP.o : textureBMP.cpp textureBMP.h
	$(CC) $(CCOPTS) textureBMP.cpp
#plane.o : plane.cpp
#        $(CC) $(CCOPTS) plane.cpp
#vector_operations.o : vector_operations.cpp
#        $(CC) $(CCOPTS) vector_operations.cpp

clean :
	rm -f *.o $(EXENAME) 2>/dev/null
