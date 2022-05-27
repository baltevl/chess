run: main
	./chess

main:
	gcc main.c -o chess -lncurses -Wunused
