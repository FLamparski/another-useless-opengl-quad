CC=clang
CFLAGS = -Wall -Wextra -x c -g -O0 -std=c11 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lGL -lGLEW -lGLU
TARGET = three

FILES = main.c helpers.c helpers.h

all:
	$(CC) $(CFLAGS) $(LDFLAGS) $(FILES) -o $(TARGET)
