PATHSOURCE = ./source/
PATHINCLUDE = ./include/
FILEBINARY = windowBinary
PATHBINARY = ./$(FILEBINARY)/


PATHGLEW = -DGLEW_STATIC ./libraries/libglew32.a
PATHGLFW = ./libraries/libglfw3.a

OGLINCLUDE = $(PATHGLEW) $(PATHGLFW) -lgdi32 -lopengl32


LO = $(wildcard $(PATHBINARY)/*.o)


CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all : main.o link run

link : $(PATHBINARY)main.o
	$(CC) $(LO) -o main.exe $(LFLAGS) $(OGLINCLUDE)

main.o : $(PATHSOURCE)main.cpp $(PATHINCLUDE)glslStrings.hpp $(PATHINCLUDE)resources.hpp $(PATHINCLUDE)tickAndFps.hpp $(PATHINCLUDE)customFunctions.hpp
	$(CC) $(CFLAGS) $(PATHSOURCE)main.cpp -o $(PATHBINARY)main.o

run :
	main

clean:
	del $(FILEBINARY)\*.o main.exe
