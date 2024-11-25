compile fork: main.o
	@gcc -o fork main.o
run:
	@./fork
main.o: main.c
	@gcc -c main.c
clean:
	rm *.o
	rm fork