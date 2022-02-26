compile:
	g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o Touhou src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

run:
	g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o Touhou src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	./Touhou.exe

run-only:
	./Touhou.exe