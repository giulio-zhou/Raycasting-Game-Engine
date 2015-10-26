CC=g++
LDLIBS=-lGLEW -framework GLUT -framework OpenGL -framework Cocoa
all:
	$(CC) $(LDLIBS) Game.cpp Main.cpp Map.cpp Player.cpp
	./a.out
clean:
	rm -f *.out
