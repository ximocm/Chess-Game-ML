#include "chess.h"

/***
 * @file chess.cpp
 * @brief Implementation of the chess.h header file
 * @author ximocm
*/

//Creates a piece of type None and color None
const Piece EmptyPiece = make_pair(None, E);

/***
 * @class Board
 * @brief Default constructor for the Board class
 * 
 * This constructor initializes the board to the starting position of a chess game
 * 
 * @return void
*/
Board::Board(){

    for (int i = 2; i < BOARD_SIZE-2; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board[i][j] = EmptyPiece;
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        board[1][i] = make_pair(White, P);
        board[BOARD_SIZE-2][i] = make_pair(Black, P);
    }
    board[0][0] = make_pair(White, R);
    board[0][1] = make_pair(White, N);
    board[0][2] = make_pair(White, B);
    board[0][3] = make_pair(White, Q);
    board[0][4] = make_pair(White, K);
    board[0][5] = make_pair(White, B);
    board[0][6] = make_pair(White, N);
    board[0][7] = make_pair(White, R);

    board[BOARD_SIZE-1][0] = make_pair(Black, R);
    board[BOARD_SIZE-1][1] = make_pair(Black, N);
    board[BOARD_SIZE-1][2] = make_pair(Black, B);
    board[BOARD_SIZE-1][3] = make_pair(Black, Q);
    board[BOARD_SIZE-1][4] = make_pair(Black, K);
    board[BOARD_SIZE-1][5] = make_pair(Black, B);
    board[BOARD_SIZE-1][6] = make_pair(Black, N);
    board[BOARD_SIZE-1][7] = make_pair(Black, R);
}

/***
 * @class Board
 * @brief Displays the board to the console
 * 
 * This function displays the board to the console
 * 
 * @return void
*/
void Board::Show(){
    for (int i = 1; i < BOARD_SIZE*2; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (i%2 == 0){
                cout << "--";
            }
            else{
                switch (board[i/2][j].first){
                    case White:
                        cout << "W";
                        break;
                    case Black:
                        cout << "B";
                        break;
                    case None:
                        cout << " ";
                        break;
                }
                switch (board[i/2][j].second){
                    case K:
                        cout << "K";
                        break;
                    case Q:
                        cout << "Q";
                        break;
                    case R:
                        cout << "R";
                        break;
                    case B:
                        cout << "B";
                        break;
                    case P:
                        cout << "P";
                        break;
                    case N:
                        cout << "N";
                        break;
                    case E:
                        cout << " ";
                        break;
                }
            }
            cout << " | ";
        }
        cout <<endl;
    }
}

/***
 * @class Board
 * @brief Makes a move on the board
 * 
 * This function makes a move on the board
 * 
 * @param mv The move to be made
 * @return void
*/
void Board::makeMove (Move mv){
    board[mv.to.first][mv.to.second] = mv.piece;
    board[mv.from.first][mv.from.second] = EmptyPiece;
}

/***
 * @class Board
 * @brief Checks if a move is legal based on the type of piece
 * 
 * This function checks if a move is legal based on the type of piece
 * 
 * @param mv The move to be made
 * @return bool True if the player is in check, false otherwise
*/
bool Board::isLegal(Move mv){
    switch (mv.piece.second){
        case P:
            return isLegalPawn(mv);
            break;
        case R:
            return isLegalRook(mv);
            break;
        case B:
            return isLegalBishop(mv);
            break;
        case N:
            return isLegalKnight(mv);
            break;
        case Q:
            return isLegalQueen(mv);
            break;
        case K:
            return isLegalKing(mv);
            break;
        default:
            return false;
    }
}

/**
 * @class Board
 * @brief Gets the piece at a given square
 * 
 * This function gets the piece at a given square
 * 
 * @param sq The square to get the piece from
 * @return Piece The piece at the given square
*/
Piece Board::getPiece(Square sq){
    return board[sq.first][sq.second];
}

bool Board::isLegalPawn(Move mv){
    if (mv.piece.first == White){
        if (mv.from.first == 1){
            if (mv.to.first == 2 || mv.to.first == 3){
                if (getPiece(mv.to) == EmptyPiece){
                    return true;
                }
            }
        }
        else{
            if (mv.to.first == mv.from.first+1 && mv.to.first < BOARD_SIZE){
                if (mv.to.second == mv.from.second+1 || mv.to.second == mv.from.second-1){
                    if (getPiece(mv.to).first == Black){
                        return true;
                    }
                }
                if (getPiece(mv.to) == EmptyPiece){
                    return true;
                }
            }
        }
    }
    else{
        if (mv.from.first == BOARD_SIZE-2){
            if (mv.to.first == BOARD_SIZE-3 || mv.to.first == BOARD_SIZE-4){
                if (getPiece(mv.to) == EmptyPiece){
                    return true;
                }
            }
        }
        else{
            if (mv.to.first == mv.from.first-1 && mv.to.first >= 0){
                if (mv.to.second == mv.from.second+1 || mv.to.second == mv.from.second-1){
                    if (getPiece(mv.to).first == White){
                        return true;
                    }
                }
                if (getPiece(mv.to) == EmptyPiece){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isLegalKnight(Move mv){
    if (mv.to.first == mv.from.first+2 || mv.to.first == mv.from.first-2){
        if (mv.to.second == mv.from.second+1 || mv.to.second == mv.from.second-1){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    if (mv.to.first == mv.from.first+1 || mv.to.first == mv.from.first-1){
        if (mv.to.second == mv.from.second+2 || mv.to.second == mv.from.second-2){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    return false;
}

bool Board::isLegalKing(Move mv){
    if (mv.to.first == mv.from.first+1 || mv.to.first == mv.from.first-1){
        if (mv.to.second == mv.from.second+1 || mv.to.second == mv.from.second-1){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    if (mv.to.first == mv.from.first){
        if (mv.to.second == mv.from.second+1 || mv.to.second == mv.from.second-1){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    if (mv.to.first == mv.from.first+1 || mv.to.first == mv.from.first-1){
        if (mv.to.second == mv.from.second){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    return false;
}

bool Board::isLegalRook(Move mv){
    if (mv.to.first == mv.from.first){
        int dist = mv.to.second - mv.from.second;
        if (dist > 0){
            for (int i = 1; i < dist-1; i++){
                if (getPiece(make_pair(mv.from.first, mv.from.second+i)) != EmptyPiece){
                    return false;
                }
            }
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
        else{
            for (int i = -1; i > dist+1; i--){
                if (getPiece(make_pair(mv.from.first, mv.from.second+i)) != EmptyPiece){
                    return false;
                }
            }
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    else if (mv.to.second == mv.from.second){
        int dist = mv.to.first - mv.from.first;
        if (dist > 0){
            for (int i = 1; i < dist-1; i++){
                if (getPiece(make_pair(mv.from.first+i, mv.from.second)) != EmptyPiece){
                    return false;
                }
            }
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
        else{
            for (int i = -1; i > dist+1; i--){
                if (getPiece(make_pair(mv.from.first+i, mv.from.second)) != EmptyPiece){
                    return false;
                }
            }
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    else{
        return false;
    }
    return false;
}

bool Board::isLegalBishop(Move mv){
    int distX = mv.to.first - mv.from.first;
    int distY = mv.to.second - mv.from.second;
    if (distX == distY){
        if (distX > 0){
            for (int i = 1; i < distX-1; i++){
                if (getPiece(make_pair(mv.from.first+i, mv.from.second+i)) != EmptyPiece){
                    return false;
                }
            }
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
        else{
            for (int i = -1; i > distX+1; i--){
                if (getPiece(make_pair(mv.from.first+i, mv.from.second+i)) != EmptyPiece){
                    return false;
                }
            }
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    else if (distX == -distY){
        if (distX > 0){
            for (int i = 1; i < distX-1; i++){
                if (getPiece(make_pair(mv.from.first+i, mv.from.second-i)) != EmptyPiece){
                    return false;
                }
            }
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
        else{
            for (int i = -1; i > distX+1; i--){
                if (getPiece(make_pair(mv.from.first+i, mv.from.second-i)) != EmptyPiece){
                    return false;
                }
            }
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    else{
        return false;
    }
    return false;
}

bool Board::isLegalQueen(Move mv){
    if (isLegalBishop(mv) || isLegalRook(mv)){
        return true;
    }
    else{
        return false;
    }
}