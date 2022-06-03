#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "main.h"
#include "game.h"

struct Position get_piece(WINDOW *boardwin){
    bool piece_choosen = false;
    int in_char = 0; 
    struct Position piece;
    
    while(!piece_choosen){
        in_char = wgetch(boardwin);
        mvwprintw(boardwin, board.focus.y*2+2, board.focus.x*4 + 4, "%c", board.field[board.focus.y][board.focus.x]);
        switch(in_char){
            case KEY_UP:
            case 'k':
                board.focus.y--;
                board.focus.y = (board.focus.y < 0) ? 0 : board.focus.y;
                break;
                
            case KEY_DOWN:
            case 'j':
                board.focus.y++;
                board.focus.y = (board.focus.y > 7) ? 7 : board.focus.y;
                break;

            case KEY_LEFT:
            case 'h':
                board.focus.x--;
                board.focus.x = (board.focus.x < 0) ? 0 : board.focus.x;
                break;

            case KEY_RIGHT:
            case 'l':
                board.focus.x++;
                board.focus.x = (board.focus.x > 7) ? 7 : board.focus.x;
                break;

            case 'q':
                piece_choosen = true;
                break;
            
            case '\n':
                if(board.field[board.focus.y][board.focus.x] != ' '){
                    piece = board.focus;
                    piece_choosen = true;
                    mvwprintw(boardwin, 19, 0, "%-54s", "");
                    mvwprintw(boardwin, 20, 0, "DEBUG:%d %d", piece.x, piece.y);
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

void get_move(WINDOW *boardwin){
    bool move_choosen = false;
    int in_char = 0; 
    //mvwprintw(boardwin, 0, 0, "%d%d%d", board.focus.x, board.focus.y, in_char);

    //piece = get_piece(boardwin);

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

            case 'q':
                move_choosen = true;
                break;

            case '\n':
                move_choosen = true;
                break;

            default:
                break;
        }
    }
}

void clear_field(){
    for (int count_y = 0;  count_y < 8; count_y++){
        for (int count_x = 0;  count_x < 8; count_x ++){
            board.field[count_y][count_x] = 32; // SPACE is ASCII 32
        }
    }
}

void update_field(){
    clear_field();
    for (int i = 0; i < ARRAY_LEN(board.pieces); i++){
        int x = board.pieces[i].position.x;
        int y = board.pieces[i].position.y;
        int offset = 32 * board.pieces[i].white;
        //printf("%c",board.pieces[i].piece - offset);
        board.field[y][x] = board.pieces[i].piece - offset;
    }
}

void draw_board(WINDOW *boardwin){
    mvwprintw(boardwin, 0, 0, "%s", "    A   B   C   D   E   F   G   H  ");
    for (int count_y = 0; count_y < 8; count_y++){
        mvwprintw(boardwin, count_y*2+1, 0, "%s", "  +---+---+---+---+---+---+---+---+");
        mvwprintw(boardwin, count_y*2+2, 0, "%d |", count_y+1);
        for (int count_x = 0; count_x < 8; count_x++){
            mvwprintw(boardwin, count_y*2+2, count_x*4 + 3, " ");
            if(count_y == board.focus.y && count_x == board.focus.x)
                wattron(boardwin, A_STANDOUT);
            mvwprintw(boardwin, count_y*2+2, count_x*4 + 4, "%c", board.field[count_y][count_x]);
            wattroff(boardwin, A_STANDOUT);
            mvwprintw(boardwin, count_y*2+2, count_x*4 + 5, " |");
        }
    }
    mvwprintw(boardwin, 17, 0, "  +---+---+---+---+---+---+---+---+");
}

void set_board(){
    char pieces_template[16] = {'k','d','t','t','l','l','s','s','b','b','b','b','b','b','b','b'};
    int files_template[16] = {4,3,0,7,2,5,1,6,0};
    for (int i = 0; i < 32; i++){
        //piece
        board.pieces[i].piece = pieces_template[i%16];
        
        //ranks and files, black and white
        if (i < 8){
            //home row white
            board.pieces[i].white = true;
            board.pieces[i].position.y = 0;
            board.pieces[i].position.x = files_template[i];
        } else if (i < 16) {
            //pawn white
            board.pieces[i].white = true;
            board.pieces[i].position.y = 1;
            board.pieces[i].position.x = i-8;
        } else if (i < 24) {
            //home row black
            board.pieces[i].white = false;
            board.pieces[i].position.y = 7;
            board.pieces[i].position.x = files_template[i-16];
        } else {
           //pawn black
            board.pieces[i].white = false;
            board.pieces[i].position.y = 6;
            board.pieces[i].position.x = i-24;
        }
    } 
}


void gameloop(){
    bool game_running = true;
    int y_max, x_max;
    board.focus.x = board.focus.y = 0;
    getmaxyx(stdscr, y_max, x_max);
    
    WINDOW *boardwin;    
    boardwin = newwin(y_max, x_max, 0, 0);
    keypad(boardwin, true); // enable keyboard input for the window.
    wrefresh(boardwin); // update the terminal screen

    board.white = true;

    while(game_running){
        update_field();
        draw_board(boardwin);
        get_move(boardwin);
        game_running = false;
    }
    delwin(boardwin);
}
