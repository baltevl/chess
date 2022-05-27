#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <ncurses.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

struct Position{
    int x;
    int y;
}; 

struct Piece{
    char piece; 
    bool white;
    int rank; 
    struct Position position;
};

struct Board{ 
    struct Piece pieces[32];
    char field[8][8];
    struct Position focus;
    bool white;
} board;


void init();

int draw_menu();

void gameloop();

void set_board();

void draw_board(WINDOW *boardwin);

void get_move(WINDOW *boardwin);

void clear_field();

void update_field();

struct Position get_next_piece(int direction,bool white);

bool is_upper_case(char piece);



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

struct Position get_next_piece(int direction, bool white){
    // direction can either be k, j, h or l 
    struct Position position;
        position.x = -1;
        position.y = -1;
    switch(direction){
        case 'k':
            if(board.focus.y == 0)
                break;
            for(int i = board.focus.y - 1; i >= 0; i--){
                if(board.field[i][board.focus.x] != ' ' && is_upper_case(board.field[i][board.focus.x]) == white){
                    position.y = i;
                    break;
                }
            }
            break;

        case 'j':
            if(board.focus.y == 7)
                break;
            for(int i = board.focus.y + 1; i <= 7; i++){
                if(board.field[i][board.focus.x] != ' ' && is_upper_case(board.field[i][board.focus.x]) == white){
                    position.y = i;
                    break;
                }
            }
            break;

        case 'h':
            if(board.focus.x == 0)
                break;
            for(int i = board.focus.x - 1; i >= 0; i--){
                if(board.field[board.focus.y][i] != ' ' && is_upper_case(board.field[board.focus.y][i]) == white){
                    position.x = i;
                    break;
                }
            }
            break;

        case 'l':
            if(board.focus.x == 7)
                break;
            for(int i = board.focus.x + 1; i <= 7; i++){
                if(board.field[board.focus.y][i] != ' ' && is_upper_case(board.field[board.focus.y][i]) == white){
                    position.x = i;
                    break;
                }
            }
            break;

        default:
            break;
    }
    return position;
}

bool is_upper_case(char piece){
    if( 64 < piece && piece < 91){
        return true;
    } else{
        return false;
    }
}

void get_move(WINDOW *boardwin){
    bool piece_choosen = false;
    bool move_choosen = false;
    int x_piece, y_piece;
    int x_move, y_move;
    int in_char = 0; 
    struct Position next_position;    
    next_position.x = -1;
    next_position.y = -1;
    //mvwprintw(boardwin, 0, 0, "%d%d%d", board.focus.x, board.focus.y, in_char);
    while(!piece_choosen){
        in_char = wgetch(boardwin);
        mvwprintw(boardwin, board.focus.y*2+2, board.focus.x*4 + 4, "%c", board.field[board.focus.y][board.focus.x]);
        switch(in_char){
            case KEY_UP:
            case 'k':
                //board.focus.y--;
                //board.focus.y = (board.focus.y < 0) ? 0 : board.focus.y;
                next_position = get_next_piece('k', board.white);
                if(next_position.y != -1)
                    board.focus.y = next_position.y;
                break;
                
            case KEY_DOWN:
            case 'j':
                //board.focus.y++;
                //board.focus.y = (board.focus.y > 7) ? 7 : board.focus.y;
                next_position = get_next_piece('j', board.white);
                if(next_position.y != -1)
                    board.focus.y = next_position.y;
                break;

            case KEY_LEFT:
            case 'h':
                //board.focus.x--;
                //board.focus.x = (board.focus.x < 0) ? 0 : board.focus.x;
                next_position = get_next_piece('h', board.white);
                if(next_position.x != -1)
                    board.focus.x = next_position.x;
                break;

            case KEY_RIGHT:
            case 'l':
                //board.focus.x++;
                //board.focus.x = (board.focus.x > 7) ? 7 : board.focus.x;
                next_position = get_next_piece('l', board.white);
                if(next_position.x != -1)
                    board.focus.x = next_position.x;
                break;

            case 'q':
                piece_choosen = true;
                move_choosen = true;
                break;
            
            case '\n':
                if(board.field[board.focus.y][board.focus.x] != ' '){
                    x_piece = board.focus.x;
                    y_piece = board.focus.y;
                    piece_choosen = true;
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
                piece_choosen = true;
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
    for (int ranks_count = 0;  ranks_count < 8; ranks_count++){
        for (int files_count = 0;  files_count < 8; files_count ++){
            board.field[ranks_count][files_count] = 32; // SPACE is ASCII 32
        }
    }
}

void update_field(){
    clear_field();
    for (int i = 0; i < ARRAY_LEN(board.pieces); i++){
        int file = board.pieces[i].position.x;
        int rank = board.pieces[i].position.y;
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
            if(ranks_count == board.focus.y && files_count == board.focus.x)
                wattron(boardwin, A_STANDOUT);
            mvwprintw(boardwin, ranks_count*2+2, files_count*4 + 4, "%c", board.field[ranks_count][files_count]);
            wattroff(boardwin, A_STANDOUT);
            mvwprintw(boardwin, ranks_count*2+2, files_count*4 + 5, " |");
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

void init(){
    initscr();
    noecho(); // disable echoing of characters on the screen
    curs_set(0); // hide the default screen cursor.
    cbreak();
    
}

int draw_menu(){
    int in_char = 0, highlight = 0; 
    char list[3][9] = {"New Game", "Settings", "Exit"};
    size_t list_len = ARRAY_LEN(list);
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
