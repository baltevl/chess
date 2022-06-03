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

void gameloop();

void set_board();

void draw_board(WINDOW *boardwin);

void get_move(WINDOW *boardwin);

void clear_field();

void update_field();

struct Position get_piece();
