#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>

#include "main.h"
#include "menu.h"

int menu(){
    int in_char = 0, highlight = 0; 
    char list[3][9] = {"New Game", "Settings", "Exit"};
    size_t list_len = ARRAY_LEN(list);
    char buffer[10];
    bool show_menu = true;
    int y_max, x_max;
    getmaxyx(stdscr, y_max, x_max);

    WINDOW *menuwin;
    menuwin = newwin(y_max, x_max, 0, 0); // create a new window
    keypad(menuwin, true); // enable keyboard input for the window.
    wrefresh(menuwin); // update the terminal screen
    
    // now print all the menu items and highlight the first one
    for(int i = 0; i < list_len; i++){
        if(i == 0) 
            wattron(menuwin, A_STANDOUT); // highlights the first item.
        sprintf(buffer, "%-9s",  list[i]);
        mvwprintw(menuwin, i, 0, "%s", buffer);
        wattroff(menuwin, A_STANDOUT);
    }
    while(show_menu){

        in_char = wgetch(menuwin); // get the input

        // right pad with spaces to make the items appear with even width.
        sprintf(buffer, "%-9s",  list[highlight]); 
        mvwprintw(menuwin, highlight, 0, "%s", buffer); 

        switch(in_char) {
            case KEY_UP:
            case 'k':
                highlight--;
                highlight = (highlight < 0) ? list_len - 1 : highlight;
                break;
            case KEY_DOWN:
            case 'j':
                highlight++;
                highlight = (highlight > list_len - 1) ? 0 : highlight;
                break;
            case 'q':
                highlight = list_len - 1;
            case '\n':
                show_menu = false;
                break;
            default:
                break;
        }

        // now highlight the next item in the list.
        wattron(menuwin, A_STANDOUT);
        sprintf(buffer, "%-9s",  list[highlight]);
        mvwprintw(menuwin, highlight, 0, "%s", buffer);
        wattroff(menuwin, A_STANDOUT);
    }
    delwin(menuwin);
    return highlight;
}
