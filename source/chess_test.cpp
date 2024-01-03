#include "chess.h"
#include <iostream>

using namespace std;

void makeMove(Board &b, string input);

int main(int argc, char** argv){
    string input = " ";
    Board b;
    while(input[0] != 0){
        if (b.gameOver()){
            cout << "Jaque mate\n";
            break;
        }
        Piece piece;
        b.Show();
        cout << "Turno de: " << b.getCurrent() << endl;
        cout << "Que quieres hacer?\n0.- Salir\nMovimiento\n>>>>";
        cin >> input;
        switch (input[0]){
        case '0':
            input[0] = 0;
            break;
        default:
            makeMove(b,input);
            break;
        }
    }
}

void makeMove(Board &b, string input){
    Move mv;
    if (input.length() != 4){
        cout << "Movimiento invalido\n";
        return;
    }
    if (input[0] < 'a' ||
        input[0] > 'h' ||
        input[1] < '1' || 
        input[1] > '8' || 
        input[2] < 'a' || 
        input[2] > 'h' || 
        input[3] < '1' || 
        input[3] > '8'){
        cout << "Movimiento invalido\n";
        return;
    }
    mv.piece = b.getPiece(Square(input[0] - 'a', input[1] - '1'));
    mv.from.first = input[0] - 'a';
    mv.from.second = input[1] - '1';
    mv.to.first = input[2] - 'a';
    mv.to.second = input[3] - '1';
    if (!b.isLegal(mv)){
        cout << "Movimiento invalido\n";
        return;
    }
    b.makeMove(mv);
    b.changeTurn();
}