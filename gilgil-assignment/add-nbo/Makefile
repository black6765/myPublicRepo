all: add_nbo_KCJ

add_nbo_KCJ: main.o add-nbo.o
	gcc -o add_nbo_KCJ main.o add_nbo.o

main.o: add_nbo.h main.c
	gcc -c -o main.o main.c

add-nbo.o: add_nbo.h add_nbo.c
	gcc -c -o add_nbo.o add_nbo.c

clean: 
	rm -f add_nbo_KCJ *.o
