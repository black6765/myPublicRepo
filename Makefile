all: add-nbo

add-nbo: add-nbo.o
	gcc -o add-nbo add-nbo.c

add-nbo.o: add-nbo.h add-nbo.c
	gcc -c -o add-nbo.o add-nbo.c

clean: 
	rm -f add-nbo *.o
