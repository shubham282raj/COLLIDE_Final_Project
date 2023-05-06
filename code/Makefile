CC = g++
CFLAGS  = -g -Wall
SDL_FLAGS = $(shell pkg-config --cflags --libs  sdl2)
INCLUDES = -I/$(CURDIR)/Game/Include/ -I/$(CURDIR)/Render/Include/	
SRC = $(wildcard Game/Source/*cpp Render/Source/*cpp) 

all : run

run : $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o run main.cpp $(SDL_FLAGS)

