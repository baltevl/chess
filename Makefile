main:
	gcc main.c -o chess -lncurses -Wunused

run: main
	./chess
