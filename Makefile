all: main.o register.o btree.o
	@gcc main.o register.o btree.o -o main

main.o: main.c
	@gcc main.c -c

register.o: register.c
	@gcc register.c -c

btree.o: btree.c
	@gcc btree.c -c

run:
	@./main	