
CFLAGS  = -g -Wall
SRC = $(wildcard Game/Source/*cpp Render/Source/*cpp) 
INCLUDES = -I./Game/Include/ -I./Render/Include/	


ifeq ($(OS),Windows_NT)
	SDL_FLAGS = -I../../include/SDL2/
else
	OS_NAME = $(shell uname)
	ifeq ($(OS_NAME), Linux)
	CC = g++
	SDL_FLAGS = $(shell pkg-config --cflags --libs  sdl2)
	endif
	ifeq ($(OS_NAME), Darwin)
	CC = clang++
	SDL_FLAGS = -I/Library/Frameworks/SDL2.framework/Headers/ -F/Library/Frameworks -framework SDL2
	endif
endif



all : run

run : $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o run main.cpp $(SDL_FLAGS)

