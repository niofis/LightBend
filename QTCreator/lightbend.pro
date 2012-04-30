TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    ../src/utils.c \
    ../src/renderer.c \
    ../src/MS3DFile.c \
    ../src/memory.c \
    ../src/main.c \
    ../src/luabindings.c \
    ../src/list.c \
    ../src/image.c \
    ../src/demos.c \
    ../src/bvh.c \
    ../src/models.c

HEADERS += \
    ../src/utils.h \
    ../src/renderer.h \
    ../src/nbvh.h \
    ../src/MS3DFile.h \
    ../src/memory.h \
    ../src/luabindings.h \
    ../src/list.h \
    ../src/image.h \
    ../src/globals.h \
    ../src/demos.h \
    ../src/bvh.h \
    ../src/models.h

LIBS += -L/usr/lib -lSDL -lSDL_gfx -llua -lm -lpng -z muldefs -pthread --openmp -lassimp

INCLUDEPATH = usr/include

QMAKE_CFLAGS += -march=native -g -Wall -O3 -ffunction-sections -DLINUX
