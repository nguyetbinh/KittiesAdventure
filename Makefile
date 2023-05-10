all:
	g++ -std=c++11 -Idata/include/SDL2  -Ldata/lib src/*.cpp -o main -lsdl2 -lsdl2main -lsdl2_image -lSDL2_mixer -lSDL2_ttf

run:
	./main


