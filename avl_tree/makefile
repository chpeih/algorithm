main: main.o util.o
	g++ -std=c++11 -g -Wall  -o a.out main.o util.o

main.o: main.cc avltree.h util.h
	g++ -c -g main.cc

util.o: util.cc util.h
	g++ -c -g util.cc

clean:
	rm -f *.o a.out
