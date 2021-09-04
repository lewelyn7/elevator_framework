all:
	gcc main.c -o main
elevator_test:
	make all
	./main