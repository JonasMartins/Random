.PHONY: clean
	
all: main

main: Main.o RayCast.o
	g++ Main.o RayCast.o -o run.exe 

Main.o: Main.cpp
	g++ -c Main.cpp

RayCast.o: RayCast.cpp
	g++ -c RayCast.cpp

clean:
	rm -f *.o *.exe