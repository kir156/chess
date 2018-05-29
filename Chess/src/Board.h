#pragma once
#include <vector>
#include "oxygine-framework.h"
#include "Piece.h"

using namespace oxygine;

class Board {
public:
    
//    spPiece     black_figurs[16];
//    spPiece     white_figurs[16];
    int         ind;
    bool    queue_to_walk;
    
    Board();
    
    void init();
    void free();
    void doUpdate(const UpdateState& us);
    
    spActor getView();
    
private:
    
};
