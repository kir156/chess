#include "Board.h"
#include <iostream>

using namespace oxygine;

Board::Board() : ind(0){}

void Board::init(){
    queue_to_walk = true;

////////////////////////// создание черных фигур
    Piece black_king;
    Piece black_queen;
    Piece black_bishop1;
    Piece black_bishop2;
    Piece black_root1;
    Piece black_root2;
    Piece black_knight1;
    Piece black_knight2;

    Piece black_pawn1;
    Piece black_pawn2;
    Piece black_pawn3;
    Piece black_pawn4;
    Piece black_pawn5;
    Piece black_pawn6;
    Piece black_pawn7;
    Piece black_pawn8;

    black_king.init(king, black, E, eight);
    black_queen.init(queen, black, D, eight);
    black_bishop1.init(bishop, black, C, eight);
    black_bishop2.init(bishop, black, F, eight);
    black_root1.init(root, black, A, eight);
    black_root2.init(root, black, H, eight);
    black_knight1.init(knight, black, B, eight);
    black_knight2.init(knight, black, G, eight);

    black_pawn1.init(pawn, black, A, seven);
    black_pawn2.init(pawn, black, B, seven);
    black_pawn3.init(pawn, black, C, seven);
    black_pawn4.init(pawn, black, D, seven);
    black_pawn5.init(pawn, black, E, seven);
    black_pawn6.init(pawn, black, F, seven);
    black_pawn7.init(pawn, black, G, seven);
    black_pawn8.init(pawn, black, H, seven);
////////////////////создание белых фигур
    Piece white_king;
    Piece white_queen;
    Piece white_bishop1;
    Piece white_bishop2;
    Piece white_root1;
    Piece white_root2;
    Piece white_knight1;
    Piece white_knight2;

    Piece white_pawn1;
    Piece white_pawn2;
    Piece white_pawn3;
    Piece white_pawn4;
    Piece white_pawn5;
    Piece white_pawn6;
    Piece white_pawn7;
    Piece white_pawn8;

    white_king.init(king, white, E, one);
    white_queen.init(queen, white, D, one);
    white_bishop1.init(bishop, white, C, one);
    white_bishop2.init(bishop, white, F, one);
    white_root1.init(root, white, A, one);
    white_root2.init(root, white, H, one);
    white_knight1.init(knight, white, B, one);
    white_knight2.init(knight, white, G, one);

    white_pawn1.init(pawn, white, A, two);
    white_pawn2.init(pawn, white, B, two);
    white_pawn3.init(pawn, white, C, two);
    white_pawn4.init(pawn, white, D, two);
    white_pawn5.init(pawn, white, E, two);
    white_pawn6.init(pawn, white, F, two);
    white_pawn7.init(pawn, white, G, two);
    white_pawn8.init(pawn, white, H, two);
}

void Board::doUpdate(const oxygine::UpdateState &us) {
}

void Board::free() {
}

























