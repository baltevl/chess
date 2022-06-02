run: chess
	./chess

chess: menu.o 
	gcc -o chess main.c menu.o -lncurses 

menu.o: 
	gcc -c menu.c -lncurses
