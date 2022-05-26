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
} board;

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


void print_board(){
    printw("    A   B   C   D   E   F   G   H \n");
    for (int ranks_count = 0; ranks_count < 8; ranks_count++){
        printw("  +---+---+---+---+---+---+---+---+\n");
        printw("%d |", ranks_count+1);
        for (int files_count = 0; files_count < 8; files_count++){
            printw(" %c |", board.field[ranks_count][files_count]);
        }
        printw("\n");
    }
    printw("  +---+---+---+---+---+---+---+---+\n");
    
    refresh();
    getch();
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

void menu(){
    WINDOW *w;
    int ch, i = 0;
    char list[3][9] = {"New Game", "Settings", "Exit"};
    size_t list_len = ARRAYLEN(list);
    char item[9];
    w = newwin(10, 14, 0, 0); // create a new window
    //box(w, 0, 0); // sets default borders for the window
    // now print all the menu items and highlight the first one
    for(i = 0; i < list_len; i++){
        if(i == 0) 
            wattron(w, A_STANDOUT); // highlights the first item.
        else
            wattroff(w, A_STANDOUT);
        sprintf(item, "%-9s",  list[i]);
        mvwprintw(w, i, 0, "%s", item);
    }
    wrefresh(w); // update the terminal screen
    i = 0;
    noecho(); // disable echoing of characters on the screen
    keypad(w, TRUE); // enable keyboard input for the window.
    curs_set(0); // hide the default screen cursor.
    // get the input
    while((ch = wgetch(w)) != 'q'){ 
        // right pad with spaces to make the items appear with even width.
        sprintf(item, "%-9s",  list[i]); 
        mvwprintw(w, i, 0, "%s", item); 
        // use a variable to increment or decrement the value based on the input.
        switch(ch) {
            case KEY_UP:
            case 'k':
                i--;
                i = (i < 0) ? list_len - 1 : i;
                break;
            case KEY_DOWN:
            case 'j':
                i++;
                i = (i > list_len -1) ? 0 : i;
                break;
        }
        // now highlight the next item in the list.
        wattron(w, A_STANDOUT);
        sprintf(item, "%-9s",  list[i]);
        mvwprintw(w, i, 0, "%s", item);
        wattroff(w, A_STANDOUT);
    }
    delwin( w );
}


int main(int argc, char* argv[]){
    initscr();
    menu();
    //set_board();
    //update_field();
    //print_board();
    endwin();
    return 0;
}
