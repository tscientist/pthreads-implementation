all: lib.o main.cpp
	g++ -o main.o lib.o main.cpp -lpthread -g
lib.o: mainLib.cpp header.hpp
	g++ -o lib.o mainLib.cpp -c -lpthread -g
clean:
	rm -rf *.o