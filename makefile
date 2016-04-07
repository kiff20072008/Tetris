all: tetris

tetris: main.o tetris.o
	g++ main.o tetris.o -o tetris

main.o: main.cpp
	g++ -c main.cpp

tetris.o: tetris.cpp
	g++ -c tetris.cpp

clean:
	rm -rf *.o tetris