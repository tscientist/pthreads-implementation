all: main.cpp mainLib.cpp
	g++ main.cpp mainLib.cpp -lpthread -o main
run: main
	./main
clean:
	rm -rf *.o