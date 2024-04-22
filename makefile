prog:  fonction.o main.o 
	gcc main.o fonction.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx -g
main.o:main.c
	gcc -c main.c -g

fonction.o:fonction.c
	gcc -c fonction.c -g


