#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "macros.h"
#include "game_ui.h"
#include "board.h"
#include "piece.h"

static WINDOW *boardwin;    

void draw_board(){
    mvwprintw(boardwin, 0, 0, "%s", "    A   B   C   D   E   F   G   H  ");
    for (int count_y = 0; count_y < 8; count_y++){
        mvwprintw(boardwin, count_y*2+1, 0, "%s", "  +---+---+---+---+---+---+---+---+");
        mvwprintw(boardwin, count_y*2+2, 0, "%d |", count_y+1);
        for (int count_x = 0; count_x < 8; count_x++){
            mvwprintw(boardwin, count_y*2+2, count_x*4 + 3, " ");
            //if(count_y == board.focus.y && count_x == board.focus.x)
//                wattron(boardwin, A_STANDOUT);
            mvwprintw(boardwin, count_y*2+2, count_x*4 + 4, "%c", board[count_y][count_x]->piece);
            wattroff(boardwin, A_STANDOUT);
            mvwprintw(boardwin, count_y*2+2, count_x*4 + 5, " |");
        }
    }
    mvwprintw(boardwin, 17, 0, "  +---+---+---+---+---+---+---+---+");
    wrefresh(boardwin); 
}


void get_move(){
    bool move_choosen = false;
    int in_char = 0; 
//    struct Piece choosen_piece;
//    char valid_move_field[8][8] = {0};
//    choosen_piece = get_piece(boardwin);

//    get_valid_moves(choosen_piece,valid_move_field);
    while(!move_choosen){
        in_char = wgetch(boardwin);
        
        switch(in_char){
            case KEY_UP:
            case 'k':
                break;

            case KEY_DOWN:
            case 'j':
                break;

            case KEY_LEFT:
            case 'h':
                break;

            case KEY_RIGHT:
            case 'l':
                break;

            case '\n':
                move_choosen = true;
                break;

            default:
                break;
        }
    }
}

/*
struct Piece get_piece(){
    bool piece_choosen = false;
    int in_char = 0; 
    struct Piece piece;
    
    while(!piece_choosen){
        in_char = wgetch(boardwin);
        mvwprintw(boardwin, board.focus.y*2+2, board.focus.x*4 + 4, "%c", board.field[board.focus.y][board.focus.x]);
        switch(in_char){
            case KEY_UP:
            case 'k':
                //board.focus.y--;
                //board.focus.y = (board.focus.y < 0) ? 0 : board.focus.y;
                MOVE_CURSOR(board.focus.y,--,<,0)
                break;
                
            case KEY_DOWN:
            case 'j':
                //board.focus.y++;
                //board.focus.y = (board.focus.y > 7) ? 7 : board.focus.y;
                MOVE_CURSOR(board.focus.y,++,>,7)
                break;

            case KEY_LEFT:
            case 'h':
                //board.focus.x--;
                //board.focus.x = (board.focus.x < 0) ? 0 : board.focus.x;
                MOVE_CURSOR(board.focus.x,--,<,0)
                break;

            case KEY_RIGHT:
            case 'l':
                //board.focus.x++;
                //board.focus.x = (board.focus.x > 7) ? 7 : board.focus.x;
                MOVE_CURSOR(board.focus.x,++,>,7)
                break;

            case '\n':
                if(board.field[board.focus.y][board.focus.x] != ' ' && is_upper_case(board.field[board.focus.y][board.focus.x]) == board.white){
                    piece.position = board.focus;
                    piece.white = board.white;
                    piece.piece = board.field[board.focus.y][board.focus.x];
                    piece_choosen = true;
                    mvwprintw(boardwin, 19, 0, "%-54s", "");
                    mvwprintw(boardwin, 20, 0, "DEBUG:%d %d", piece.position.x, piece.position.y);
                } 
                break;

            default:
                mvwprintw(boardwin, 19, 0, "Use h,j,k,l or arrow keys to move and Enter to confirm");

                break;
        }
//        mvwprintw(boardwin, 0, 0, "%d%d%c ", board.focus.x, board.focus.y, in_char);
        wattron(boardwin, A_STANDOUT);
        mvwprintw(boardwin, board.focus.y*2+2, board.focus.x*4 + 4, "%c", board.field[board.focus.y][board.focus.x]);
        wattroff(boardwin, A_STANDOUT);
    }
    return piece;

}
*/


void game_ui_init(){
    //create new window of max size
    int y_max, x_max;
    getmaxyx(stdscr, y_max, x_max);
    boardwin = newwin(y_max, x_max, 0, 0);

    // enable keyboard input for the window.
    keypad(boardwin, true); 

    // update the terminal screen
    wrefresh(boardwin); 
}

void game_ui_exit(){
    delwin(boardwin);
}
