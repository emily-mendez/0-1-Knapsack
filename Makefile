all: submission

submission: Main.o Algorithms.o
	g++ Main.o Algorithms.o -o submission

Main.o: Main.cpp Algorithms.h
	g++ -c Main.cpp

Algorithms.o: Algorithms.cpp Algorithms.h
	g++ -c Algorithms.cpp

clean:
	rm -f *.o submission