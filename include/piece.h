#define KING 'K'
#define QUEEN 'Q'
#define ROCK 'R'
#define BISHOP 'B'
#define KNIGHT 'N'
#define PAWN 'P'

#ifndef PIECE_H_
#define PIECE_H_
typedef struct Position Position; 
typedef struct Piece Piece;

struct Position{
    int x;
    int y;
}; 

struct Piece{
    char type; 
    bool white;
    Position position;
};
#endif

Piece *piece_init(char type,bool white,int pos_x, int pos_y);
