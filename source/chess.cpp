#include "chess.h"

/***
 * @file chess.cpp
 * @brief Implementation of the chess.h header file
 * @author ximocm
*/

//Creates a piece of type None and color None
const Piece EmptyPiece = make_pair(None, E);
const char Letters[BOARD_SIZE] = {'a','b','c','d','e','f','g','h'};

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
    board[0][3] = make_pair(White, K);
    board[0][4] = make_pair(White, Q);
    board[0][5] = make_pair(White, B);
    board[0][6] = make_pair(White, N);
    board[0][7] = make_pair(White, R);

    board[BOARD_SIZE-1][0] = make_pair(Black, R);
    board[BOARD_SIZE-1][1] = make_pair(Black, N);
    board[BOARD_SIZE-1][2] = make_pair(Black, B);
    board[BOARD_SIZE-1][3] = make_pair(Black, K);
    board[BOARD_SIZE-1][4] = make_pair(Black, Q);
    board[BOARD_SIZE-1][5] = make_pair(Black, B);
    board[BOARD_SIZE-1][6] = make_pair(Black, N);
    board[BOARD_SIZE-1][7] = make_pair(Black, R);

    cout << "Board initialized" << endl;
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
    cout << "1    2    3    4    5    6    7    8" << endl;
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
        if (i%2 == 0){
            cout << endl;
        }
        else{
            cout << Letters[i/2] << endl;
        }
    }
    cout << "1    2    3    4    5    6    7    8" << endl;
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
    if (mv.piece.second == P){
        if (mv.piece.first == White && mv.to.first == BOARD_SIZE-1){
            mv.piece.second = Q;
            board[mv.to.first][mv.to.second] = mv.piece;
        }
        else if (mv.piece.first == Black && mv.to.first == 0){
            mv.piece.second = Q;
            board[mv.to.first][mv.to.second] = mv.piece;
        }
    }
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
        if (mv.from.first == 1 && mv.from.second == mv.to.second){
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
                else if (mv.to.second == mv.from.second){
                    if (getPiece(mv.to) == EmptyPiece){
                        return true;
                    }
                }
            }
        }
    }
    else{
        if (mv.from.first == BOARD_SIZE-2 && mv.from.second == mv.to.second){
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
            }
        }
    }
    return false;
}

bool Board::isLegalKnight(Move mv){
    if (mv.to.first == mv.from.first+2 && mv.to.first < BOARD_SIZE){
        if(mv.to.second == mv.from.second+1 && mv.to.second < BOARD_SIZE){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
        else if(mv.to.second == mv.from.second-1 && mv.to.second >= 0){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    else if (mv.to.first == mv.from.first-2 && mv.to.first >= 0){
        if(mv.to.second == mv.from.second+1 && mv.to.second < BOARD_SIZE){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
        else if(mv.to.second == mv.from.second-1 && mv.to.second >= 0){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    else if (mv.to.first == mv.from.first+1 && mv.to.first < BOARD_SIZE){
        if(mv.to.second == mv.from.second+2 && mv.to.second < BOARD_SIZE){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
        else if(mv.to.second == mv.from.second-2 && mv.to.second >= 0){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
    }
    else if (mv.to.first == mv.from.first-1 && mv.to.first >= 0){
        if(mv.to.second == mv.from.second+2 && mv.to.second < BOARD_SIZE){
            if (getPiece(mv.to).first != mv.piece.first){
                return true;
            }
        }
        else if(mv.to.second == mv.from.second-2 && mv.to.second >= 0){
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
                Board temp = *this;
                temp.makeMove(mv);
                if (!temp.isCheck(mv.piece.first)){
                    return true;
                }
                return false;
            }
        }
    }
    if (mv.to.first == mv.from.first){
        if (mv.to.second == mv.from.second+1 || mv.to.second == mv.from.second-1){
            if (getPiece(mv.to).first != mv.piece.first){
                Board temp = *this;
                temp.makeMove(mv);
                if (!temp.isCheck(mv.piece.first)){
                    return true;
                }
                return false;
            }
        }
    }
    if (mv.to.first == mv.from.first+1 || mv.to.first == mv.from.first-1){
        if (mv.to.second == mv.from.second){
            if (getPiece(mv.to).first != mv.piece.first){
                Board temp = *this;
                temp.makeMove(mv);
                if (!temp.isCheck(mv.piece.first)){
                    return true;
                }
                return false;
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

/**
 * @brief Checks if the given color is in check.
 * 
 * This function determines whether the king of the specified color is under threat from
 * enemy pieces on the chessboard.
 * 
 * @param clr The color of the king to check for check.
 * @return True if the king is in check, false otherwise.
 */
bool Board::isCheck(Color clr){
    Square king = getKing(clr);
    //Check for knights
    if (make_pair(clr, N) == getPiece(make_pair(king.first+2, king.second+1)) ||
        make_pair(clr, N) == getPiece(make_pair(king.first+2, king.second-1)) ||
        make_pair(clr, N) == getPiece(make_pair(king.first-2, king.second+1)) ||
        make_pair(clr, N) == getPiece(make_pair(king.first-2, king.second-1)) ||
        make_pair(clr, N) == getPiece(make_pair(king.first+1, king.second+2)) ||
        make_pair(clr, N) == getPiece(make_pair(king.first+1, king.second-2)) ||
        make_pair(clr, N) == getPiece(make_pair(king.first-1, king.second+2)) ||
        make_pair(clr, N) == getPiece(make_pair(king.first-1, king.second-2))){
            return true;
    }
    //Check for pawns
    if (clr == White){
        if (make_pair(clr, P) == getPiece(make_pair(king.first+1, king.second+1)) ||
            make_pair(clr, P) == getPiece(make_pair(king.first+1, king.second-1))){
                return true;
        }
    }
    else{
        if (make_pair(clr, P) == getPiece(make_pair(king.first-1, king.second+1)) ||
            make_pair(clr, P) == getPiece(make_pair(king.first-1, king.second-1))){
                return true;
        }
    }
    //Check for rooks and queens
    for (int i = king.first+1; i < BOARD_SIZE; i++){
        if (getPiece(make_pair(i, king.second)) != EmptyPiece){
            if (getPiece(make_pair(i, king.second)) == make_pair(clr, R) ||
                getPiece(make_pair(i, king.second)) == make_pair(clr, Q)){
                    return true;
            }
            else{
                break;
            }
        }
    }
    for (int i = king.first-1; i >= 0; i--){
        if (getPiece(make_pair(i, king.second)) != EmptyPiece){
            if (getPiece(make_pair(i, king.second)) == make_pair(clr, R) ||
                getPiece(make_pair(i, king.second)) == make_pair(clr, Q)){
                    return true;
            }
            else{
                break;
            }
        }
    }
    for (int i = king.second+1; i < BOARD_SIZE; i++){
        if (getPiece(make_pair(king.first, i)) != EmptyPiece){
            if (getPiece(make_pair(king.first, i)) == make_pair(clr, R) ||
                getPiece(make_pair(king.first, i)) == make_pair(clr, Q)){
                    return true;
            }
            else{
                break;
            }
        }
    }
    for (int i = king.second-1; i >= 0; i--){
        if (getPiece(make_pair(king.first, i)) != EmptyPiece){
            if (getPiece(make_pair(king.first, i)) == make_pair(clr, R) ||
                getPiece(make_pair(king.first, i)) == make_pair(clr, Q)){
                    return true;
            }
            else{
                break;
            }
        }
    }
    //Check for bishops and queens
    for (int i = 1; i < BOARD_SIZE; i++){
        if (king.first+i < BOARD_SIZE && king.second+i < BOARD_SIZE){
            if (getPiece(make_pair(king.first+i, king.second+i)) != EmptyPiece){
                if (getPiece(make_pair(king.first+i, king.second+i)) == make_pair(clr, B) ||
                    getPiece(make_pair(king.first+i, king.second+i)) == make_pair(clr, Q)){
                        return true;
                }
                else{
                    break;
                }
            }
        }
        else{
            break;
        }
    }
    for (int i = 1; i < BOARD_SIZE; i++){
        if (king.first-i >= 0 && king.second-i >= 0){
            if (getPiece(make_pair(king.first-i, king.second-i)) != EmptyPiece){
                if (getPiece(make_pair(king.first-i, king.second-i)) == make_pair(clr, B) ||
                    getPiece(make_pair(king.first-i, king.second-i)) == make_pair(clr, Q)){
                        return true;
                }
                else{
                    break;
                }
            }
        }
        else{
            break;
        }
    }
    for (int i = 1; i < BOARD_SIZE; i++){
        if (king.first+i < BOARD_SIZE && king.second-i >= 0){
            if (getPiece(make_pair(king.first+i, king.second-i)) != EmptyPiece){
                if (getPiece(make_pair(king.first+i, king.second-i)) == make_pair(clr, B) ||
                    getPiece(make_pair(king.first+i, king.second-i)) == make_pair(clr, Q)){
                        return true;
                }
                else{
                    break;
                }
            }
        }
        else{
            break;
        }
    }
    for (int i = 1; i < BOARD_SIZE; i++){
        if (king.first-i >= 0 && king.second+i < BOARD_SIZE){
            if (getPiece(make_pair(king.first-i, king.second+i)) != EmptyPiece){
                if (getPiece(make_pair(king.first-i, king.second+i)) == make_pair(clr, B) ||
                    getPiece(make_pair(king.first-i, king.second+i)) == make_pair(clr, Q)){
                        return true;
                }
                else{
                    break;
                }
            }
        }
        else{
            break;
        }
    }
    return false;
}

/**
 * @brief Checks if the game is over.
 * 
 * This function determines whether the game is over by checking if either king is in checkmate.
 * 
 * @return True if the game is over, false otherwise.
 */
bool Board::gameOver(){
    if(isCheck(White)){
        Move mv;
        mv.piece = make_pair(White, K);
        Square king = getKing(White);
        mv.from = king;
        for (int i = king.first-1; i <= king.first+1; i++){
            for (int j = king.second-1; j <= king.second+1; j++){
                mv.to = make_pair(i,j);
                if (isLegal(mv)){
                    return false;
                }
            }
        }
    }
    else if(isCheck(Black)){
        Move mv;
        mv.piece = make_pair(Black, K);
        Square king = getKing(Black);
        mv.from = king;
        for (int i = king.first-1; i <= king.first+1; i++){
            for (int j = king.second-1; j <= king.second+1; j++){
                mv.to = make_pair(i,j);
                if (isLegal(mv)){
                    return false;
                }
            }
        }
    }
    else{
        return false;
    }
    return true;
}

/**
 * @brief Gets the square of the king of the specified color.
 * 
 * This function gets the square of the king of the specified color.
 * 
 * @param clr The color of the king to get the square of.
 * @return The square of the king of the specified color.
 */
Square Board::getKing(Color clr){
    Square king;
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (board[i][j] == make_pair(clr, K)){
                king = make_pair(i,j);
            }
        }
    }
    return king;
}

/**
 * @brief Gets a list of all legal moves for the specified color.
 * 
 * This function gets a list of all legal moves for the specified color.
 * 
 * @param clr The color of the player to get the moves for.
 * @return A list of all legal moves for the specified color.
 */
Moves Board::getMoves(Color clr){
    Moves moves;
    Move mv;
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            mv.from = make_pair(i,j);
            mv.piece.second = board[i][j].second;
            mv.piece.first = board[i][j].first;
            switch (mv.piece.second){
                case E:
                    break;
                case P:
                    if (mv.piece.first == White && clr == White){
                        if(i < BOARD_SIZE-1){
                            mv.to = make_pair(i+1,j);
                            if (isLegalPawn(mv)){
                                moves.push_back(mv);
                            }
                        }
                        if(j > 0){
                            mv.to = make_pair(i+1,j-1);
                            if (isLegalPawn(mv)){
                                moves.push_back(mv);
                            }
                        }
                        if(j < BOARD_SIZE-1){
                            mv.to = make_pair(i+1,j+1);
                            if (isLegalPawn(mv)){
                                moves.push_back(mv);
                            }
                        }
                    }
                    if (mv.piece.first == Black && clr == Black){
                        if (i > 0){
                            mv.to = make_pair(i-1,j);
                            if(isLegalPawn(mv)){
                                moves.push_back(mv);
                            }
                        }
                        if(j > 0){
                            mv.to = make_pair(i-1,j-1);
                            if (isLegalPawn(mv)){
                                moves.push_back(mv);
                            }
                        }
                        if(j < BOARD_SIZE-1){
                            mv.to = make_pair(i-1,j+1);
                            if (isLegalPawn(mv)){
                                moves.push_back(mv);
                            }
                        }
                    }
                    break;
                case R:
                /*
                    for (int k = 1; k < (j - BOARD_SIZE)*-1; k++){
                        mv.to = make_pair(i,j-k);
                        if (isLegalRook(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 1; k < (i-BOARD_SIZE)*-1; k++){
                        mv.to = make_pair(i-k,j);
                        if (isLegalRook(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 1; k < (BOARD_SIZE-j); k++){
                        mv.to = make_pair(i,j+k);
                        if (isLegalRook(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 1; k < (BOARD_SIZE-j); k++){
                        mv.to = make_pair(i+k,j);
                        if (isLegalRook(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    */
                    break;
                case B:
                /*
                    for (int k = 0; k < BOARD_SIZE; k++){
                        mv.to = make_pair(i+k,j+k);
                        if (isLegalBishop(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 0; k < BOARD_SIZE; k++){
                        mv.to = make_pair(i+k,j-k);
                        if (isLegalBishop(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 0; k < BOARD_SIZE; k++){
                        mv.to = make_pair(i-k,j+k);
                        if (isLegalBishop(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 0; k < BOARD_SIZE; k++){
                        mv.to = make_pair(i-k,j-k);
                        if (isLegalBishop(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    */
                    break;
                case N:
                    mv.to = make_pair(i+2,j+1);
                    if (isLegalKnight(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i+2,j-1);
                    if (isLegalKnight(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i-2,j+1);
                    if (isLegalKnight(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i-2,j-1);
                    if (isLegalKnight(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i+1,j+2);
                    if (isLegalKnight(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i+1,j-2);
                    if (isLegalKnight(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i-1,j+2);
                    if (isLegalKnight(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i-1,j-2);
                    if (isLegalKnight(mv)){
                        moves.push_back(mv);
                    }
                    break;
                case Q:
                /*
                    for (int k = 1; k < (j - BOARD_SIZE)*-1; k++){
                        mv.to = make_pair(i,j-k);
                        if (isLegalQueen(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 1; k < (i-BOARD_SIZE)*-1; k++){
                        mv.to = make_pair(i-k,j);
                        if (isLegalQueen(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 1; k < (BOARD_SIZE-j); k++){
                        mv.to = make_pair(i,j+k);
                        if (isLegalQueen(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 1; k < (BOARD_SIZE-j); k++){
                        mv.to = make_pair(i+k,j);
                        if (isLegalQueen(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 0; k < BOARD_SIZE; k++){
                        mv.to = make_pair(i+k,j+k);
                        if (isLegalQueen(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 0; k < BOARD_SIZE; k++){
                        mv.to = make_pair(i+k,j-k);
                        if (isLegalQueen(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 0; k < BOARD_SIZE; k++){
                        mv.to = make_pair(i-k,j+k);
                        if (isLegalQueen(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    for (int k = 0; k < BOARD_SIZE; k++){
                        mv.to = make_pair(i-k,j-k);
                        if (isLegalQueen(mv)){
                            moves.push_back(mv);
                        }
                        else{
                            break;
                        }
                    }
                    */
                    break;
                case K:
                /*
                    mv.to = make_pair(i+1,j+1);
                    if (isLegalKing(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i+1,j);
                    if (isLegalKing(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i+1,j-1);
                    if (isLegalKing(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i,j+1);
                    if (isLegalKing(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i,j-1);
                    if (isLegalKing(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i-1,j+1);
                    if (isLegalKing(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i-1,j);
                    if (isLegalKing(mv)){
                        moves.push_back(mv);
                    }
                    mv.to = make_pair(i-1,j-1);
                    if (isLegalKing(mv)){
                        moves.push_back(mv);
                    }
                    */
                    break;
            }
        }
    }
    return moves;
}

/**
 * @brief Changes the turn.
 * 
 * This function changes the turn.
 * 
 * @return void
 */
void Board::changeTurn(){
    if (current == White){
        current = Black;
    }
    else{
        current = White;
    }
}

bool Board::playerMove(Piece piece){
    string input;
    Move mv;
    mv.piece = piece;
    cout << "\n Dime la casilla origen:";
    cin >> input;
    if(getPiece(Square(input[0]-'a',input[1]-'1')) == mv.piece){
        mv.from = Square(input[0]-'a',input[1]-'1');
        cout << "\n Dime la casilla destino:";
        cin >> input;
        mv.to = Square(input[0]-'a',input[1]-'1');
        if(isLegal(mv)){
            makeMove(mv);
            return true;
        }
        else{
            cout << "\n Movimiento ilegal\n";
            return false;
        }
    }
    else{
        cout << "\n Esta pieza no se encuentra en esa casilla\n";
        return false;
    }
}

Color Board::getCurrent(){
    return current;
}