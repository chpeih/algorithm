main: main.o util.o
	g++ -std=c++11 -g -Wall  -o a.out main.o util.o

main.o: main.cc avltree.h util.h
	g++ -c main.cc

util.o: util.cc util.h
	g++ -c util.cc

clean:
	rm -f *.o a.out
