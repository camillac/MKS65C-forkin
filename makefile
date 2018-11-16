all: fork_proc.o
	gcc fork_proc.o

clean:
	rm -f *~ *.gch* a.out *.o *#*

run:
	./a.out

fork_proc.o: fork_proc.c
	gcc -c fork_proc.c
