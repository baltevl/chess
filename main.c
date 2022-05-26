#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <ncurses.h>

#define ARRAYLEN(x) (sizeof(x) / sizeof((x)[0]))

struct Piece{
    char piece; 
    bool white;
    int file;
    int rank; 
};

struct Board { 
    struct Piece pieces[32];
    char field[8][8];
    int x_focus;
    int y_focus;
} board;


void get_move();

void clear_field();

void update_field();

void draw_board();

void set_board();

void gameloop();

void init();

int draw_menu();

int main(int argc, char* argv[]){
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

void get_move(){
    char piece_input[20], move_input[20];
    printf("Enter piece you want to move: ");
    do {
        scanf("%s", &piece_input);
    } while (piece_input);
}

void clear_field(){
    for (int ranks_count = 0;  ranks_count < 8; ranks_count++){
        for (int files_count = 0;  files_count < 8; files_count ++){
            board.field[ranks_count][files_count] = 32; // SPACE is ASCII 32
        }
    }
}

void update_field(){
    clear_field();
    for (int i = 0; i < ARRAYLEN(board.pieces); i++){
        int file = board.pieces[i].file;
        int rank = board.pieces[i].rank;
        int offset = 32 * board.pieces[i].white;
        //printf("%c",board.pieces[i].piece - offset);
        board.field[rank][file] = board.pieces[i].piece - offset;
    }
}


void draw_board(WINDOW *boardwin){
    mvwprintw(boardwin, 0, 0, "%s", "    A   B   C   D   E   F   G   H  ");
    for (int ranks_count = 0; ranks_count < 8; ranks_count++){
        mvwprintw(boardwin, ranks_count*2+1, 0, "%s", "  +---+---+---+---+---+---+---+---+");
        mvwprintw(boardwin, ranks_count*2+2, 0, "%d |", ranks_count+1);
        for (int files_count = 0; files_count < 8; files_count++){
            mvwprintw(boardwin, ranks_count*2+2, files_count*4 + 3, " ");
            if(ranks_count == board.x_focus && files_count == board.y_focus)
                wattron(boardwin, A_STANDOUT);
            mvwprintw(boardwin, ranks_count*2+2, files_count*4 + 4, "%c", board.field[ranks_count][files_count]);
            wattroff(boardwin, A_STANDOUT);
            mvwprintw(boardwin, ranks_count*2+2, files_count*4 + 5, " |");
        }
    }
    mvwprintw(boardwin, 17, 0, "  +---+---+---+---+---+---+---+---+");
    
    wgetch(boardwin);
}

void set_board(){
    char pieces_template[16] = {'k','d','t','t','l','l','s','s','b','b','b','b','b','b','b','b'};
    int ranks_template[4] = {0,1,7,6};
    int files_template[16] = {4,3,0,7,2,5,1,6,0};
    for (int i = 0; i < 32; i++){
        //piece
        board.pieces[i].piece = pieces_template[i%16];
        
        //ranks and files, black and white
        if (i < 8){
            //home row white
            board.pieces[i].white = true;
            board.pieces[i].rank = 0;
            board.pieces[i].file = files_template[i];
        } else if (i < 16) {
            //pawn white
            board.pieces[i].white = true;
            board.pieces[i].rank = 1;
            board.pieces[i].file = i-8;
        } else if (i < 24) {
            //home row black
            board.pieces[i].white = false;
            board.pieces[i].rank = 7;
            board.pieces[i].file = files_template[i-16];
        } else {
           //pawn black
            board.pieces[i].white = false;
            board.pieces[i].rank = 6;
            board.pieces[i].file = i-24;
        }
    } 
}

void init(){
    initscr();
    noecho(); // disable echoing of characters on the screen
    curs_set(0); // hide the default screen cursor.
    cbreak();
    
}

int draw_menu(){
    int in_char, highlight = 0; 
    char list[3][9] = {"New Game", "Settings", "Exit"};
    size_t list_len = ARRAYLEN(list);
    char buffer[9];
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
                show_menu = false;
                highlight = list_len - 1;
            case '\n':
                show_menu = false;
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

void gameloop(){
    bool game_running = true;
    int y_max, x_max;
    board.x_focus, board.y_focus = 0;
    getmaxyx(stdscr, y_max, x_max);
    
    WINDOW *boardwin;    
    boardwin = newwin(y_max, x_max, 0, 0);
    keypad(boardwin, true); // enable keyboard input for the window.
    wrefresh(boardwin); // update the terminal screen

    while(game_running){
        update_field();
        draw_board(boardwin);
    }
    delwin(boardwin);
}
