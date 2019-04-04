main: main.o
	g++ -std=c++11 -g -Wall  -o a.out main.o

main.o: main.cc binary_search.h
	g++ -c -g main.cc

clean:
	rm -f *.o a.out
