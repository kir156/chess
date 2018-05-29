#include "oxygine-framework.h"
#include <functional>
#include "Piece.h"
#include "Board.h"

using namespace oxygine;

Resources res;
Board board;

void example_preinit() {}

//called from main.cpp
void example_init()
{
    res.loadXML("/data/xml/resources.xml");
    
    spSprite field = new Sprite;
    field->setResAnim(res.getResAnim("field"));
    field->attachTo(getStage());
    field->setSize(500, 500);
    
    board.init();
}


//called each frame from main.cpp
void example_update()
{
}

//called each frame from main.cpp
void example_destroy()
{
    board.free();
    res.free();
}
