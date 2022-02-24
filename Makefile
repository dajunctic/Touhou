all:
	g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o Touhou src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

run:
	./Touhou.exe