# Build and Run Shell.c
.PHONY: all
all : shell

shell : shell.o
	gcc -O3 shell.o -o shell

shell.o: shell.c
	gcc -O3 -std=c11 -c shell.c

.PHONY: run
run: shell.c
	ulimit -u
	./shell

.PHONY: clean
clean :
	@rm -f shell shell.o

.PHONY: cleanall
cleanall :
	@make clean 