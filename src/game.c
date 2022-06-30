#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "game_ui.h"
#include "board.h"

void game_init(){
    board_init();
    game_ui_init();

}

void game_run(){
    bool game_running = true;
    while(game_running){
        draw_board();
    }
}

void game_exit(){
    game_ui_exit();
}

void game(){
    game_init();
    game_run();
    game_exit();
}
