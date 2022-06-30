#include <ncurses.h>

#include "menu.h"
#include "game.h"

void ncurses_init(){
    initscr();
    noecho(); // disable echoing of characters on the screen
    curs_set(0); // hide the default screen cursor.
    cbreak();
    
}

int main(int argc, char* argv[]){
    ncurses_init();
    bool exit = false;
    int choice = 2;
    while(!exit){
        choice = menu();
        switch(choice){
            case 0:
                game();
                break;
            case 1:
                break; 
            case 2:
                exit = true;
                break;
       }
    }
    endwin();
    return 0;
}


