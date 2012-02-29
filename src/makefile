.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS) $<


# Macros

CC = gcc
CFLAGS = -g -Wall -O3 -lSDL -lSDL_gfx -pthread --openmp  -ffunction-sections -z muldefs -DLINUX -llua -lm
SRC = demos.c demos.h main.c renderer.c memory.c luabindings.c MS3DFile.c bvh.c bvh.h MS3DFile.h luabindings.h memory.h renderer.h utils.c utils.h globals.h
OBJ = main.o demos.o renderer.o utils.o memory.o luabindings.o MS3DFile.o bvh.o


# Reglas explicitas

all: $(OBJ)
	$(CC) $(CFLAGS) -o ../bin/ligthbend.run $(OBJ)

clean:
	$(RM) $(OBJ) crtu

# Reglas implicitas
bvh.o: bvh.c bvh.h globals.h 
MS3DFile.o: MS3DFile.c MS3DFile.h
luabindings.o: luabindings.c luabindings.h MS3DFile.h bvh.h
memory.o: memory.c memory.h
renderer.o: renderer.c renderer.h globals.h memory.h luabindings.h
demos.o: demos.c demos.h globals.h MS3DFile.h bvh.h
utils.o: utils.c utils.h globals.h 
main.o: main.c renderer.h demos.h utils.h globals.h memory.h luabindings.h MS3DFile.h bvh.h

