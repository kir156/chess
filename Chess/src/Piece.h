#pragma once
#include "oxygine-framework.h"
#include "DraggableSprite.h"

using namespace oxygine;

enum piece_type {
    king    = 0,
    queen   = 1,
    root    = 2,
    knight  = 3,
    bishop  = 4,
    pawn    = 5
};

enum color_type {
    black   = 0,
    white   = 1
};

enum coord {A = 49, B = 106, C = 164, D = 221, E = 279, F = 336, G = 393, H = 453,
     one = 453, two = 393, three = 336, four = 279, five = 221, six = 164, seven = 106, eight = 49
};

DECLARE_SMART(Piece, spPiece);

extern const Vector2 sizePiece;

class Piece : Actor{
    
public:
    Piece();
    void init(int type, int color, int _x, int _y);
    void free();
    
    void onMouseDown(Event* event);
    void onMouseUp(Event* event);
    void doUpdate(const UpdateState& us);
    
    int         _getX() const;
    int         _getY() const;
    int         _getColor() const;
    spSprite    _getView() const;
    
private:
    bool    queue_to_walk;
    bool    is_choosed;
    
    int     _color;
    int     _type;
    int     _x;
    int     _y;
    
    spSprite    _view;
};


