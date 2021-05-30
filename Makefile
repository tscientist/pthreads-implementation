all: main.cpp mainLib.cpp
	g++ main.cpp mainLib.cpp -lpthread -o main
input: main
	./main
clean:
	rm -rf *.o