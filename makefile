all: link

link: main.o graphics.o
	gcc -o projet main.o graphics.o -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype

graphics.o: lib/graphics.c
	gcc -c lib/graphics.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o projet
