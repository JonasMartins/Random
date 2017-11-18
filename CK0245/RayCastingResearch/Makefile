all: run 

run: main.o raycasting.o
	g++ main.o raycasting.o ./exe/run.exe

main.o: Main.cpp
	g++ Main.cpp

raycasting.o: RayCasting.cpp
	g++ RayCasting.cpp

out:
	./exe/run.exe

clean_images:
	rm -rf ./*.ppm
	rm -rf ./images/*.ppm
clean:
	rm -rf ./exe/*.exe
