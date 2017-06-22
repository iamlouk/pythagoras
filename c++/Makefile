SDLCFLAGS := $(shell sdl2-config --cflags)
SDLLFLAGS := $(shell sdl2-config --libs)
CFLAGS="-Wall"

.PHONY: clean

prog: main.cpp rectangle.o vector.o
	g++ $(CFLAGS) $(SDLCFLAGS) -c main.cpp
	g++ $(CFLAGS) $(SDLCFLAGS) $(SDLLFLAGS) -o prog main.o rectangle.o vector.o

rectangle.o: rectangle.cpp rectangle.hpp
	g++ $(CFLAGS) $(SDLCFLAGS) -c rectangle.cpp

vector.o: vector.cpp vector.hpp
	g++ $(CFLAGS) $(SDLCFLAGS) -c vector.cpp

clean:
	rm -f main.o
	rm -f rectangle.o
	rm -f vector.o
	rm -f prog
