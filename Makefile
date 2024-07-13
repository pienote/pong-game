CFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

all:
	g++ src/*.cpp -o game.exe $(CFLAGS)

run:
	g++ src/*.cpp -o game.exe $(CFLAGS)
	game.exe
