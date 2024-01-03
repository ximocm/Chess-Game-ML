#ifndef _CHESS_H
#define _CHESS_H

#define DEB true
#include <iostream>
#include <list>
#include <string>
#include <float.h>

#define BOARD_SIZE 8
using namespace std;

typedef pair<int, int> Square;
typedef list<Square> SqList;

enum Color {White, Black, None};

enum Type {K,Q,R,B,P,N,E};

typedef pair<Color,Type> Piece;
typedef list<Piece> Pieces;

struct Move{
    Square from;
    Square to;
    Piece piece;
};
typedef list<Move> Moves;

class Board{
    public:
        Board();
        void Show();
        bool isCheck(Color clr);
        bool isLegal(Move mv);
        void makeMove(Move mv);
        Piece getPiece(Square sq);
        bool gameOver();
        Square getKing(Color clr);
        Moves getMoves(Color clr);
        void changeTurn();
        bool playerMove(Piece p);
        Color getCurrent();


    private:
        Color current = White;
        Piece board[BOARD_SIZE][BOARD_SIZE];
        bool isLegalPawn(Move mv);
        bool isLegalRook(Move mv);
        bool isLegalBishop(Move mv);
        bool isLegalKnight(Move mv);
        bool isLegalQueen(Move mv);
        bool isLegalKing(Move mv);
};

#endif