all: puzzle clean

puzzle: puzzle.o
	gcc -g -lreadline -o puzzle puzzle.o

puzzle.o: puzzle.c
	gcc -g -c puzzle.c

clean:
	-rm *.o *~
