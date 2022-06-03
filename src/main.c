#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "main.h"
#include "menu.h"
#include "game.h"


int main(int argc, char* argv[]){
    printf("Hello World");
    init();
    int choice = 2;
    choice = draw_menu();
    switch(choice){
        case 0:
            set_board();
            gameloop();
            break;
        case 1:
            break; 
        case 2:
            break;
    }
    endwin();
    return 0;
}

bool is_upper_case(char piece){
    if( 64 < piece && piece < 91){
        return true;
    } else{
        return false;
    }
}

void init(){
    initscr();
    noecho(); // disable echoing of characters on the screen
    curs_set(0); // hide the default screen cursor.
    cbreak();
    
}
