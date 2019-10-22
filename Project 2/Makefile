project2: main.o simpleStack.o exceptions.o
	g++ -o project2 main.o simpleStack.o exceptions.o

main.o: main.cc simpleStack.h
	g++ -c main.cc

simpleStack.o: simpleStack.cc simpleStack.h exceptions.h
	g++ -c simpleStack.cc



