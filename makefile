kelvin: main.o libro.o editorial.o
	g++ main.o libro.o editorial.o -o exe
main.o: main.cpp libro.cpp editorial.cpp
	g++ -c main.cpp
libro.o: libro.cpp libro.h
	g++ -c libro.cpp
editorial.o: editorial.cpp editorial.h
	g++ -c editorial.cpp
