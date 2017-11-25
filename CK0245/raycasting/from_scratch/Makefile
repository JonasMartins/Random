.PHONY: clean
	
all: main

main: Main.o RayCast.o
	g++ Main.o RayCast.o -o run.exe 

Main.o: Main.cpp
	g++ -g -c Main.cpp

RayCast.o: RayCast.cpp
	g++ -g -c RayCast.cpp

clean:
	rm -f *.o *.exe