all: link

link: main.o graphics.o maze.o
	gcc -o markOfTheWar main.o graphics.o maze.o -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype

graphics.o: lib/graphics.c
	gcc -c lib/graphics.c

maze.o: maze.c header.h
	gcc -c maze.c

main.o: main.c header.h maze.h lib/graphics.h
	gcc -c main.c

clean:
	rm -rf *.o projet
